#
# File: cpmerge.py
# Author: vididvidid 
# Created: 2026-06-09 14:32:13
#

#!/usr/bin/env python3
import sys
import os
import re

# Regex to capture local vs system includes
LOCAL_INCLUDE_RE = re.compile(r'^\s*#include\s+"([^"]+)"')
SYSTEM_INCLUDE_RE = re.compile(r'^\s*#include\s+<([^>]+)>')

def merge_source(entry_file):
    visited_files = set()
    system_headers = set()
    merged_lines = []

    def process_file(filepath):
        abs_path = os.path.abspath(filepath)
        
        # Prevent infinite loops and duplicate inclusions
        if abs_path in visited_files:
            return
        visited_files.add(abs_path)

        if not os.path.exists(abs_path):
            print(f"// WARNING: Could not find local include -> {abs_path}", file=sys.stderr)
            return

        base_dir = os.path.dirname(abs_path)
        
        try:
            with open(abs_path, 'r', encoding='utf-8') as f:
                for line in f:
                    # 1. Handle Local Includes
                    local_match = LOCAL_INCLUDE_RE.match(line)
                    if local_match:
                        include_filename = local_match.group(1)
                        next_file = os.path.join(base_dir, include_filename)
                        process_file(next_file)
                        continue
                    
                    # 2. Handle System Includes
                    sys_match = SYSTEM_INCLUDE_RE.match(line)
                    if sys_match:
                        system_headers.add(line.strip())
                        continue
                    
                    # 3. Strip #pragma once
                    if line.strip() == "#pragma once":
                        continue
                        
                    merged_lines.append(line)
                    
        except Exception as e:
            print(f"// ERROR reading {abs_path}: {e}", file=sys.stderr)

    # Start recursive parsing
    process_file(entry_file)

    # Assemble the final flat file content
    final_output = []
    for header in sorted(system_headers):
        final_output.append(header + "\n")
    
    final_output.append("\n")
    final_output.extend(merged_lines)

    return "".join(final_output)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: cpmerge <source_file.c>", file=sys.stderr)
        sys.exit(1)
        
    input_file = sys.argv[1]
    
    if not os.path.exists(input_file):
        print(f"[-] Error: Input file '{input_file}' does not exist.", file=sys.stderr)
        sys.exit(1)

    # 1. Setup target directory (~/cp/submit)
    output_dir = os.path.expanduser("~/cp/submit")
    os.makedirs(output_dir, exist_ok=True)
    
    # 2. Build target filename (submit_x.c)
    base_filename = os.path.basename(input_file)
    output_filename = f"submit_{base_filename}"
    output_filepath = os.path.join(output_dir, output_filename)
    
    # 3. Merge files
    merged_code = merge_source(input_file)
    
    # 4. Write to destination
    try:
        with open(output_filepath, 'w', encoding='utf-8') as f:
            f.write(merged_code)
        print(f"[+] Successfully generated: {output_filepath}")
    except Exception as e:
        print(f"[-] Failed to write merged file: {e}", file=sys.stderr)
        sys.exit(1)
