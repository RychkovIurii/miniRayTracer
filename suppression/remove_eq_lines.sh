#!/bin/bash

if [[ $# -ne 1 ]]; then
    echo "Usage: $0 <filename>"
    exit 1
fi

filename="$1"

if [[ ! -f "$filename" ]]; then
    echo "Error: File '$filename' not found!"
    exit 1
fi

grep -v '^==' "$filename" > "${filename}.tmp"

mv "${filename}.tmp" "$filename"

echo "Lines starting with '==' have been removed from '$filename'."
