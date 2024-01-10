#!/bin/sh

[ -e words.txt ] && rm words.txt
{
    echo "the day is sunny the the"
    echo "the sunny is is"
} >>words.txt

# Read from the file words.txt and output the word frequency list to stdout.

# cat words.txt | tr -s ' ' '\n' | sort | uniq -c | sort -r | awk '{print $NF" "$1}'
tr -s ' ' '\n' <words.txt | sort | uniq -c | sort -r | awk '{print $NF" "$1}'

[ -e words.txt ] && rm words.txt

exit 0
