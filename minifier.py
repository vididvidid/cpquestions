#
# File: minifier.py
# Author: vididvidid 
# Created: 2026-06-01 04:21:37
#

#!/usr/bin/env python2.7
#     C Minify Copyright (C) 2015 Alexandre Baron
#     This program comes with ABSOLUTELY NO WARRANTY; for details read LICENSE.
#     This is free software, and you are welcome to redistribute it
#     under certain conditions; read LICENSE for details.

import argparse
import sys
import re
import os  # SEEK_END etc.
import fileinput # read from STDIN
import itertools

# Ops: ops that may be spaced out in the code but we can trim the whitespace before and after
# Spaced ops are operators that we need to append with one trailing space because of their syntax (e.g. keywords).
# NB: theses ops are the SUPPORTED ones and these lists may not be complete as per the Standard
OPS = [
    '+', '-', '*', '/', '%', '++', '--',
    '+=', '-=', '*=', '/=', '%=', '=', '==', '!=',
    '&&', '||', '!', '&', '|', '^', '<<', '>>',
    '<', '>', '<=', '>=', '<<=', '>>=', '&=', '|=', '^=', ',',
    '(', ')', '{', '}', ';', 'else', ':', '::', '?'
]
SPACED_OPS = ['else']
UNARY_OPS= ["+", "-", "&", "!", "*"]
PREPROCESSOR_TOKEN = '#'

# Standard C keywords and common library functions to protect from obfuscation
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
    "solve" # Protected so the AI knows where the logic starts
}


def remove_everything_between(subs1, subs2, line):
    regex = re.compile(subs1 + r'.*' + subs2)
    return regex.sub('', line)


def remove_everything_before(subs, line):
    regex = re.compile(r'.*' + subs)
    return regex.sub('', line)


def remove_everything_past(subs, line):
    regex = re.compile(subs + r'.*')
    return regex.sub('', line)


def remove_multiline_comments(lines):
    start, end = '/*', '*/'
    escaped_start, escaped_end = '/\*', '\*/'
    in_comment = False
    newlines = []
    for line in lines:
        if not in_comment:
            start_pos = line.find(start)
            if start_pos != -1:
                in_comment = True
                end_pos = line.find(end)
                # inline multiline comment
                if start_pos < end_pos:
                    line = remove_everything_between(escaped_start, escaped_end, line)
                    in_comment = False
                else:
                    line = remove_everything_past(escaped_start, line)
        else:
            end_pos = line.find(end)
            if end_pos != -1:
                line = remove_everything_before(escaped_end, line)
                in_comment = False
                start_pos = line.find(start)
                # start of another comment on the same line
                if start_pos != -1:
                    line = remove_everything_past(escaped_start, line)
                    in_comment = True
            else:
                line = ''
        newlines.append(line)
    return newlines


def remove_inline_comments(lines):
    return map(lambda x: remove_everything_past('//', x), lines)


def minify_operator(op):
    """Returns a function applying a regex to strip away spaces on each side of an operator
    Makes a special escape for operators that could be mistaken for regex control characters."""
    to_compile = " *{} *".format(re.escape(op))
    regex = re.compile(to_compile)
    repl = op
    if op in SPACED_OPS:
        repl += " "
    return lambda string: regex.sub(repl, string)


def fix_spaced_ops(minified_txt):
    """This will walk the spaced ops list and search the text for all "[OP] {" sequences occurrences
    and replace them by "[OP]{" since there is no operator in the C syntax for which the spacing
    between the op and the '{' is mandatory."""
    for op in SPACED_OPS:
        pattern = "{} {{".format(op)  # {{ for literal braces
        repl = "{}{{".format(op)
        minified_txt = re.sub(pattern, repl, minified_txt)
    return minified_txt


def fix_unary_operators(lines):
    """Ops processing can have eliminated necessary space when using unary ops"""
    regex_unary_ops = '[{}]'.format(''.join(UNARY_OPS))
    regex_unary_ops = re.escape(regex_unary_ops)
    pattern = "^(#[a-z]+ +[\w\d]+)([{}][\w\d]+)$".format(regex_unary_ops)
    repl = r'\1' + " " + r'\2'
    for (idx, line) in enumerate(lines):
        if is_preprocessor_directive(line):
            for op in UNARY_OPS:
                line = re.sub(pattern, repl, line)
            lines[idx] = line
    return lines


def clear_whitespace_first_pass(lines):
    """Given a list of lines, clears all leading/trailing whitespace"""
    lines = map(lambda x: x.replace('\t', ' '), lines)
    lines = map(lambda x: x.strip(' '), lines)
    return list(lines)


def reinsert_preprocessor_newlines(lines):
    """Preprocessor directives should stay on their own line even minified"""
    for idx, line in enumerate(lines):
        if is_preprocessor_directive(line) or (
         idx != len(lines)-1 and is_preprocessor_directive(lines[idx+1])):
            lines[idx] = lines[idx] + '\n'
    return lines


def fix_duplicate_newlines(file):
    regex = re.compile('[\n]{2,}')
    return regex.sub('\n', file)


def is_preprocessor_directive(line):
    return line.startswith(PREPROCESSOR_TOKEN)


def collapse_includes(minified_txt):
    """Finds all #include directives and collapses them into an array-like format."""
    includes = []
    pattern = re.compile(r'#include\s*(?:<([^>]+)>|("[^"]+"))\s*')
    
    for match in pattern.finditer(minified_txt):
        val = match.group(1) if match.group(1) else match.group(2)
        includes.append(val)
        
    minified_txt = pattern.sub('', minified_txt)
    
    if includes:
        include_str = "#include [ " + ", ".join(includes) + " ]\n"
        minified_txt = include_str + minified_txt.lstrip()
        
    return minified_txt


def generate_short_names(exclude_set):
    """Generates sequential variable names: a, b, c... aa, ab, etc."""
    chars = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
    for length in itertools.count(1):
        for p in itertools.product(chars, repeat=length):
            name = ''.join(p)
            if name not in exclude_set:
                yield name


def replace_identifiers(minified_txt):
    """Replaces identifiers > 3 chars with short, auto-generated names, protecting includes."""
    include_line = ""
    
    # 1. HIDE the custom #include array line so it doesn't get scanned
    if minified_txt.startswith("#include ["):
        parts = minified_txt.split(']\n', 1)
        if len(parts) == 2:
            include_line = parts[0] + "]\n"
            minified_txt = parts[1]

    # 2. Split code by string literals to avoid replacing words inside quotes
    tokens = re.split(r'("[^"\\]*(?:\\.[^"\\]*)*")', minified_txt)
    
    existing_identifiers = set()
    # Only scan the non-string segments (even indices) for identifiers
    for i in range(0, len(tokens), 2):
        existing_identifiers.update(re.findall(r'\b[a-zA-Z_]\w*\b', tokens[i]))
    
    to_replace = {}
    exclude_set = C_KEYWORDS.copy()
    exclude_set.update(existing_identifiers)
    
    short_name_gen = generate_short_names(exclude_set)
    
    # Identify which names meet the criteria for replacement
    for ident in existing_identifiers:
        if len(ident) > 3 and ident not in C_KEYWORDS:
            to_replace[ident] = next(short_name_gen)
            
    # Apply replacements
    for i in range(0, len(tokens), 2):
        code_part = tokens[i]
        for orig, short in to_replace.items():
            code_part = re.sub(r'\b' + orig + r'\b', short, code_part)
        tokens[i] = code_part
        
    minified_txt = ''.join(tokens)
    
    # 3. Output the replacement mapping and stitch the include line back on top
    if to_replace:
        mapping_str = "replaced_names [" + ", ".join(f"{k}={v}" for k, v in to_replace.items()) + "]\n"
        minified_txt = include_line + mapping_str + minified_txt
    else:
        minified_txt = include_line + minified_txt
            
    return minified_txt


def strip_fast_io(minified_txt):
    """Removes common C++ fast I/O boilerplate which AI doesn't need to read."""
    io_patterns = [
        r'ios_base::sync_with_stdio\([^)]*\);?',
        r'cin\.tie\([^)]*\);?',
        r'cout\.tie\([^)]*\);?'
    ]
    for pattern in io_patterns:
        minified_txt = re.sub(pattern, '', minified_txt)
    return minified_txt


def collapse_cp_main(minified_txt):
    """
    Finds standard CP main loops and replaces them with a tiny pseudo-code tag.
    Detects if there is a 't' loop or just a single run.
    """
    # Pattern for multiple test cases: while(...) { solve(); }
    pattern_n = re.compile(r'int main\(\)\{.*?while\([^)]+\)\{?solve\(\);?\}?.*?return 0;\}')
    if pattern_n.search(minified_txt):
        return pattern_n.sub('[MAIN: loop t:n -> solve()]', minified_txt)
        
    # Pattern for single test case: solve();
    pattern_1 = re.compile(r'int main\(\)\{.*?solve\(\);?.*?return 0;\}')
    if pattern_1.search(minified_txt):
        return pattern_1.sub('[MAIN: loop t:1 -> solve()]', minified_txt)
        
    return minified_txt


def minify_source(orig_source, args=None):
    keep_newlines = getattr(args, 'keep_newlines', False)
    keep_multiline_comments = getattr(args, 'keep_multiline', False)
    keep_inline_comments = getattr(args, 'keep_inline', False)

    lines = orig_source.split('\n')
    lines = clear_whitespace_first_pass(lines)
    
    if keep_newlines is False:
        lines = reinsert_preprocessor_newlines(lines)

    for op in OPS:
        lines = map(minify_operator(op), lines)
        
    if keep_inline_comments is False:
        lines = remove_inline_comments(lines)
    if keep_multiline_comments is False:
        lines = remove_multiline_comments(lines)
        
    multi_spaces = re.compile(r'[  ]+ *')
    lines = list(map(lambda string: multi_spaces.sub(' ', string), lines))
    lines = fix_unary_operators(lines)

    minified = ""
    if keep_newlines is True:
        minified = args.newline.join(lines)
    else:
        minified = fix_duplicate_newlines(''.join(lines))

    minified = fix_spaced_ops(minified)
    minified = strip_fast_io(minified)
    minified = collapse_includes(minified)
    
    # Run replacement FIRST so the custom [MAIN] tags aren't modified
    minified = replace_identifiers(minified)
    minified = collapse_cp_main(minified)

    # ADD THE AI PROMPT PREAMBLE HERE
    ai_preamble = "System Instruction: This is minified CP code. Includes are an array, CP boilerplate main() is collapsed, and variables > 3 chars are replaced. The mapping is below. Focus on `solve()`, it's the main entry point to logic. Please read this code and stand by for questions.\n\n"
    minified = ai_preamble + minified

    return minified


def get_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("files", nargs='+', help="Input files")
    parser.add_argument("-n", "--names",
                        help="Show name of processed files",
                        action='store_true')
    parser.add_argument("-s", "--stats",
                        help="Show statistics on minified version",
                        action='store_true')
    parser.add_argument("-m", "--keep-multiline",
                        help="Don't strip multiline comments (/* ... */)",
                        action='store_true')
    parser.add_argument("-i", "--keep-inline",
                        help="Do not strip inline comments (// ...)",
                        action='store_true')
    parser.add_argument("-w", "--keep-newlines",
                        help="Keep newline control characters",
                        action='store_true')
    args = parser.parse_args()
    return args


def get_minification_delta(source_text, minified_text):
    orig_size = len(source_text)
    mini_size = len(minified_text)
    delta = orig_size - mini_size
    return delta


def print_additional_info(orig_source, minified_source, filename, args):
    if args.names is True:
        print("{}:".format(filename))

    if args.stats is True:
        orig_size = len(orig_source)
        mini_size = len(minified_source)
        delta = get_minification_delta(orig_source, minified_source)
        if orig_size != 0:
            print(
                "Original: {0} characters, Minified: {1} characters, {2} removed ({3:.1f}%)"
                .format(orig_size, mini_size, delta, (float(delta) / float(orig_size)) * 100.0)
            )


def process_files(args):
    for filename in args.files:
        orig_source_code = ""
        newline = None 

        if filename == "-":
            for line in fileinput.input():
                orig_source_code += line
        else:
            with open(filename, 'r') as f:
                orig_source_code = f.read()
                newline = f.newlines

        if type(newline) is tuple:
            print(
                "Mixed newlines are unsupported, skipping file {}."
                .format(filename)
            )
            continue

        args.newline = newline
        minified_source_code = minify_source(orig_source_code, args)

        print_additional_info(
            orig_source_code, minified_source_code, filename, args
        )

        print(minified_source_code)


def main():
    args = get_args()
    process_files(args)


if __name__ == "__main__":
    main()
