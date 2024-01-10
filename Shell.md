# Shell

## [192. Word Frequency](https://leetcode.com/problems/word-frequency/)

<details><summary>Description</summary>

```text
Write a bash script to calculate the frequency of each word in a text file words.txt.

For simplicity sake, you may assume:

words.txt contains only lowercase characters and space ' ' characters.
Each word must consist of lowercase characters only.
Words are separated by one or more whitespace characters.
```

```text
Example:
Assume that words.txt has the following content:
```

```bash
the day is sunny the the
the sunny is is
```

```text
Your script should output the following, sorted by descending frequency:
```

```bash
the 4
is 3
sunny 2
day 1
```

```text
Note:
- Don't worry about handling ties, it is guaranteed that each word's frequency count is unique.
- Could you write it in one-line using Unix pipes?
```

</details>

<details><summary>Shell</summary>

```bash
# Read from the file words.txt and output the word frequency list to stdout.

# cat words.txt | tr -s ' ' '\n' | sort | uniq -c | sort -r | awk '{print $NF" "$1}'
tr -s ' ' '\n' < words.txt | sort | uniq -c | sort -r | awk '{print $NF" "$1}'
```

</details>

## [194. Transpose File](https://leetcode.com/problems/transpose-file/)

<details><summary>Description</summary>

```text
Given a text file file.txt, transpose its content.

You may assume that each row has the same number of columns, and each field is separated by the ' ' character.
```

```text
Example:
If file.txt has the following content:
```

```bash
name age
alice 21
ryan 30
```

```text
Output the following:
```

```bash
name alice ryan
age 21 30
```

</details>

<details><summary>Shell</summary>

```bash
# Read from the file file.txt and print its transposed content to stdout.

count=$(head -n1 file.txt | wc -w)
# for i in $(seq 1 ${count}); do echo $(cut -d' ' -f${i} file.txt); done
for i in $(seq 1 "${count}"); do cut -d' ' -f"${i}" file.txt | awk NF=NF RS= OFS=' '; done
```

</details>

## [195. Tenth Line](https://leetcode.com/problems/tenth-line/)

<details><summary>Description</summary>

```text
Given a text file file.txt, print just the 10th line of the file.
```

```text
Example:

Assume that file.txt has the following content:
```

```bash
Line 1
Line 2
Line 3
Line 4
Line 5
Line 6
Line 7
Line 8
Line 9
Line 10
```

```text
Your script should output the tenth line, which is:
```

```bash
Line 10
```

```text
Note:
1. If the file contains less than 10 lines, what should you output?
2. There's at least three different solutions. Try to explore all possibilities.
```

</details>

<details><summary>Shell</summary>

```bash
# Read from the file file.txt and output the tenth line to stdout.

# tail -n+10 file.txt | head -1

# awk 'NR==10' file.txt

sed -n 10p file.txt
```

</details>
