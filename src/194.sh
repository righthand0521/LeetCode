#!/bin/sh

[ -e file.txt ] && rm file.txt
{
    echo "name age"
    echo "alice 21"
    echo "ryan 30"
} >>file.txt

# Read from the file file.txt and print its transposed content to stdout.

count=$(head -n1 file.txt | wc -w)
# for i in $(seq 1 ${count}); do echo $(cut -d' ' -f${i} file.txt); done
for i in $(seq 1 "${count}"); do cut -d' ' -f"${i}" file.txt | awk NF=NF RS= OFS=' '; done

[ -e file.txt ] && rm file.txt

exit 0
