#
# File: minifier.py
# Author: vididvidid 
# Created: 2026-06-01 04:21:37
#

#!/usr/bin/env python2.7
import argparse
import sys
import re
import os
import fileinput
import itertools

# Ops that we can trim whitespace around
OPS = [
    '+', '-', '*', '/', '%', '++', '--',
    '+=', '-=', '*=', '/=', '%=', '=', '==', '!=',
    '&&', '||', '!', '&', '|', '^', '<<', '>>',
    '<', '>', '<=', '>=', '<<=', '>>=', '&=', '|=', '^=', ',',
    '(', ')', '{', '}', ';', 'else', ':', '::', '?'
]
SPACED_OPS = ['else']
UNARY_OPS = ["+", "-", "&", "!", "*"]
PREPROCESSOR_TOKEN = '#'

C_KEYWORDS = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "inline", "int", "long", "register", "restrict", "return", "short",
    "signed", "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while", "_Alignas", "_Alignof",
    "_Atomic", "_Bool", "_Complex", "_Generic", "_Imaginary", "_Noreturn",
    "_Static_assert", "_Thread_local", "include", "define", "undef",
    "ifdef", "ifndef", "endif", "elif", "pragma", "error", "line",
    "printf", "scanf", "strlen", "main", "NULL", "EOF", "stdin", "stdout", "stderr",
    "solve" # Protected
}

def remove_everything_between(subs1, subs2, line):
    return re.sub(re.escape(subs1) + r'.*?' + re.escape(subs2), '', line)

def remove_everything_before(subs, line):
    return re.sub(r'.*' + re.escape(subs), '', line)

def remove_everything_past(subs, line):
    return re.sub(re.escape(subs) + r'.*', '', line)

def remove_multiline_comments(lines):
    start, end = '/*', '*/'
    in_comment = False
    newlines = []
    for line in lines:
        if not in_comment:
            start_pos = line.find(start)
            if start_pos != -1:
                in_comment = True
                end_pos = line.find(end)
                if start_pos < end_pos:
                    line = line[:start_pos] + line[end_pos+2:]
                    in_comment = False
                else:
                    line = line[:start_pos]
        else:
            end_pos = line.find(end)
            if end_pos != -1:
                line = line[end_pos+2:]
                in_comment = False
                start_pos = line.find(start)
                if start_pos != -1:
                    line = line[:start_pos]
                    in_comment = True
            else:
                line = ''
        newlines.append(line)
    return newlines

def remove_inline_comments(lines):
    return [re.sub(r'//.*', '', x) for x in lines]

def minify_operator(op):
    to_compile = r" *{} *".format(re.escape(op))
    regex = re.compile(to_compile)
    repl = op + (" " if op in SPACED_OPS else "")
    return lambda string: regex.sub(repl, string)

def fix_spaced_ops(minified_txt):
    for op in SPACED_OPS:
        minified_txt = re.sub(r"{} \{{".format(op), r"{}{{".format(op), minified_txt)
    return minified_txt

def fix_unary_operators(lines):
    regex_unary_ops = re.escape(''.join(UNARY_OPS))
    pattern = r"^(#[a-z]+ +[\w\d]+)([{}][\w\d]+)$".format(regex_unary_ops)
    repl = r'\1 \2'
    for idx, line in enumerate(lines):
        if line.startswith(PREPROCESSOR_TOKEN):
            lines[idx] = re.sub(pattern, repl, line)
    return lines

def is_preprocessor_directive(line):
    return line.startswith(PREPROCESSOR_TOKEN)

def reinsert_preprocessor_newlines(lines):
    for idx, line in enumerate(lines):
        if is_preprocessor_directive(line) or (idx != len(lines)-1 and is_preprocessor_directive(lines[idx+1])):
            lines[idx] = lines[idx] + '\n'
    return lines

def strip_useless_directives(minified_txt):
    """Removes pragmas and standard namespace declarations to save tokens."""
    minified_txt = re.sub(r'#pragma[^\n]*\n?', '', minified_txt)
    minified_txt = re.sub(r'using\s+namespace\s+std\s*;', '', minified_txt)
    return minified_txt

def collapse_includes(minified_txt):
    includes = []
    pattern = re.compile(r'#include\s*(?:<([^>]+)>|("[^"]+"))\s*')
    for match in pattern.finditer(minified_txt):
        val = match.group(1) if match.group(1) else match.group(2)
        includes.append(val)
    minified_txt = pattern.sub('', minified_txt)
    if includes:
        minified_txt = "#include [ " + ", ".join(includes) + " ]\n" + minified_txt.lstrip()
    return minified_txt

def collapse_defines(minified_txt):
    """Finds all #define statements and collapses them into a token-friendly array."""
    defines = []
    pattern = re.compile(r'#define\s+([A-Za-z0-9_]+)\s+([^\n]+)\n?')
    for match in pattern.finditer(minified_txt):
        name, value = match.group(1), match.group(2).strip()
        defines.append(f"{name}={value}")
        
    minified_txt = pattern.sub('', minified_txt)
    
    if defines:
        define_str = "#define [ " + ", ".join(defines) + " ]\n"
        if minified_txt.startswith("#include ["):
            parts = minified_txt.split(']\n', 1)
            if len(parts) == 2:
                minified_txt = parts[0] + "]\n" + define_str + parts[1]
        else:
            minified_txt = define_str + minified_txt
            
    return minified_txt

def generate_short_names(exclude_set):
    chars = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
    for length in itertools.count(1):
        for p in itertools.product(chars, repeat=length):
            name = ''.join(p)
            if name not in exclude_set:
                yield name

def replace_identifiers(minified_txt):
    include_define_lines = ""
    
    header_pattern = re.compile(r'^(?:#(?:include|define)\s*\[.*?\]\n)+')
    header_match = header_pattern.match(minified_txt)
    if header_match:
        include_define_lines = header_match.group(0)
        minified_txt = minified_txt[header_match.end():]

    tokens = re.split(r'("[^"\\]*(?:\\.[^"\\]*)*")', minified_txt)
    existing_identifiers = set()
    for i in range(0, len(tokens), 2):
        existing_identifiers.update(re.findall(r'\b[a-zA-Z_]\w*\b', tokens[i]))
    
    to_replace = {}
    exclude_set = C_KEYWORDS.copy()
    exclude_set.update(existing_identifiers)
    short_name_gen = generate_short_names(exclude_set)
    
    for ident in existing_identifiers:
        if len(ident) > 3 and ident not in C_KEYWORDS:
            to_replace[ident] = next(short_name_gen)
            
    for i in range(0, len(tokens), 2):
        code_part = tokens[i]
        for orig, short in to_replace.items():
            code_part = re.sub(r'\b' + orig + r'\b', short, code_part)
        tokens[i] = code_part
        
    minified_txt = ''.join(tokens)
    
    if to_replace:
        mapping_str = "replaced [" + ", ".join(f"{k}={v}" for k, v in to_replace.items()) + "]\n"
        minified_txt = include_define_lines + mapping_str + minified_txt
    else:
        minified_txt = include_define_lines + minified_txt
            
    return minified_txt

def strip_fast_io(minified_txt):
    io_patterns = [
        r'ios_base::sync_with_stdio\([^)]*\);?',
        r'cin\.tie\([^)]*\);?',
        r'cout\.tie\([^)]*\);?'
    ]
    for pattern in io_patterns:
        minified_txt = re.sub(pattern, '', minified_txt)
    return minified_txt

def collapse_cp_main(minified_txt):
    pattern_n = re.compile(r'int main\(\)\{.*?while\([^)]+\)\{?solve\(\);?\}?.*?return 0;\}')
    if pattern_n.search(minified_txt):
        return pattern_n.sub('[MAIN: loop t:n -> solve()]', minified_txt)
        
    pattern_1 = re.compile(r'int main\(\)\{.*?solve\(\);?.*?return 0;\}')
    if pattern_1.search(minified_txt):
        return pattern_1.sub('[MAIN: loop t:1 -> solve()]', minified_txt)
        
    return minified_txt

def minify_source(orig_source, args=None):
    lines = orig_source.split('\n')
    lines = [x.replace('\t', ' ').strip() for x in lines]
    lines = reinsert_preprocessor_newlines(lines)

    for op in OPS:
        lines = map(minify_operator(op), lines)
        
    lines = remove_inline_comments(lines)
    lines = remove_multiline_comments(lines)
        
    multi_spaces = re.compile(r'[  ]+ *')
    lines = [multi_spaces.sub(' ', string) for string in lines]
    lines = fix_unary_operators(lines)

    minified = re.sub(r'[\n]{2,}', '\n', ''.join(lines))
    minified = fix_spaced_ops(minified)
    
    minified = strip_useless_directives(minified)
    minified = strip_fast_io(minified)
    minified = collapse_includes(minified)
    minified = collapse_defines(minified)
    
    minified = replace_identifiers(minified)

    # --- FLAG LOGIC IMPLEMENTATION ---
    is_cp = getattr(args, 'cp', False)
    
    if is_cp:
        minified = collapse_cp_main(minified)
        ai_preamble = "System Instruction: Minified CP code. `std` namespace implied. Headers/Macros mapped. Variables >3 chars replaced. Focus on `solve()`. Read and standby.\n\n"
    else:
        # Default PRO behavior
        ai_preamble = "System Instruction: Minified C/C++ code. `std` namespace implied. Headers/Macros mapped. Variables >3 chars replaced. Read and standby.\n\n"

    minified = ai_preamble + minified

    return minified

def process_files(args):
    for filename in args.files:
        orig_source_code = ""
        if filename == "-":
            for line in fileinput.input():
                orig_source_code += line
        else:
            with open(filename, 'r') as f:
                orig_source_code = f.read()

        minified_source_code = minify_source(orig_source_code, args)
        print(minified_source_code)

def get_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("files", nargs='+', help="Input files")
    
    # Mutually exclusive group so they can't pass both by accident
    mode_group = parser.add_mutually_exclusive_group()
    mode_group.add_argument("--cp", action='store_true', help="Use Competitive Programming mode (collapses main, targets solve())")
    mode_group.add_argument("--pro", action='store_true', help="Use Professional mode (leaves main intact)")
    
    return parser.parse_args()

if __name__ == "__main__":
    process_files(get_args())
