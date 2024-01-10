#!/bin/sh

[ -e file.txt ] && rm file.txt
{
    echo "Line 1"
    echo "Line 2"
    echo "Line 3"
    echo "Line 4"
    echo "Line 5"
    echo "Line 6"
    echo "Line 7"
    echo "Line 8"
    echo "Line 9"
    echo "Line 10"
} >>file.txt

# Read from the file file.txt and output the tenth line to stdout.

# tail -n+10 file.txt | head -1

# awk 'NR==10' file.txt

sed -n 10p file.txt

[ -e file.txt ] && rm file.txt

exit 0
