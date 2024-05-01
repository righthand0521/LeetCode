# [Trie](https://en.wikipedia.org/wiki/Trie)

## [208. Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree/)

- [Official](https://leetcode.cn/problems/implement-trie-prefix-tree/solutions/717239/shi-xian-trie-qian-zhui-shu-by-leetcode-ti500/)

<details><summary>Description</summary>

```text
A trie (pronounced as "try") or prefix tree is a tree data structure
used to efficiently store and retrieve keys in a dataset of strings.
There are various applications of this data structure, such as autocomplete and spellchecker.

Implement the Trie class:
- Trie()
  Initializes the trie object.
- void insert(String word)
  Inserts the string word into the trie.
- boolean search(String word)
  Returns true if the string word is in the trie (i.e., was inserted before), and false otherwise.
- boolean startsWith(String prefix)
  Returns true if there is a previously inserted string word that has the prefix prefix, and false otherwise.

Example 1:
Input
["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
[[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
Output
[null, null, true, false, true, null, true]

Explanation
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // return True
trie.search("app");     // return False
trie.startsWith("app"); // return True
trie.insert("app");
trie.search("app");     // return True

Constraints:
1 <= word.length, prefix.length <= 2000
word and prefix consist only of lowercase English letters.
At most 3 * 10^4 calls in total will be made to insert, search, and startsWith.
```

</details>

<details><summary>C</summary>

```c
#define MAX_CHAR (26)  // word and prefix consist only of lowercase English letters.
typedef struct Trie {
    struct Trie* children[MAX_CHAR];
    bool isEnd;
} Trie;
Trie* trieCreate() {
    Trie* pRetVal = (Trie*)malloc(sizeof(Trie));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal->children, 0, sizeof(pRetVal->children));
    pRetVal->isEnd = false;

    return pRetVal;
}
void trieInsert(Trie* obj, char* word) {
    int len = strlen(word);

    int ch;
    int i;
    for (i = 0; i < len; ++i) {
        ch = word[i] - 'a';
        if (obj->children[ch] == NULL) {
            obj->children[ch] = trieCreate();
            if (obj->children[ch] == NULL) {
                return;
            }
        }
        obj = obj->children[ch];
    }
    obj->isEnd = true;
}
bool trieSearch(Trie* obj, char* word) {
    bool retVal = false;

    int len = strlen(word);

    int ch;
    int i;
    for (i = 0; i < len; ++i) {
        ch = word[i] - 'a';
        if (obj->children[ch] == NULL) {
            return retVal;
        }
        obj = obj->children[ch];
    }
    retVal = obj->isEnd;

    return retVal;
}
bool trieStartsWith(Trie* obj, char* prefix) {
    bool retVal = false;

    int len = strlen(prefix);

    int ch;
    int i;
    for (i = 0; i < len; ++i) {
        ch = prefix[i] - 'a';
        if (obj->children[ch] == NULL) {
            return retVal;
        }
        obj = obj->children[ch];
    }
    retVal = true;

    return retVal;
}
void trieFree(Trie* obj) {
    int i;
    for (i = 0; i < MAX_CHAR; ++i) {
        if (obj->children[i]) {
            trieFree(obj->children[i]);
        }
    }
    free(obj);
}
/**
 * Your Trie struct will be instantiated and called as such:
 * Trie* obj = trieCreate();
 * trieInsert(obj, word);
 * bool param_2 = trieSearch(obj, word);
 * bool param_3 = trieStartsWith(obj, prefix);
 * trieFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
// https://leetcode.cn/problems/implement-trie-prefix-tree/solutions/721110/gong-shui-san-xie-yi-ti-shuang-jie-er-we-esm9/
#define MAX_CHAR (26)  // word and prefix consist only of lowercase English letters.
class Trie {
   private:
    Trie* child[MAX_CHAR];
    bool isEnd;

   public:
    Trie() {
        for (int i = 0; i < MAX_CHAR; ++i) {
            child[i] = nullptr;
        }
        isEnd = false;
    }
    ~Trie() {
        for (int i = 0; i < MAX_CHAR; ++i) {
            if (child[i] != nullptr) {
                delete child[i];
            }
        }
    }
    void insert(string word) {
        Trie* root = this;
        for (char x : word) {
            int cur = x - 'a';
            if (root->child[cur] == nullptr) {
                root->child[cur] = new Trie();
            }
            root = root->child[cur];
        }
        root->isEnd = true;
    }
    bool search(string word) {
        bool retVal = false;

        Trie* root = this;
        for (char x : word) {
            int cur = x - 'a';
            if (root->child[cur] == nullptr) {
                return retVal;
            }
            root = root->child[cur];
        }
        retVal = root->isEnd;

        return retVal;
    }
    bool startsWith(string prefix) {
        bool retVal = false;

        Trie* root = this;
        for (char x : prefix) {
            int cur = x - 'a';
            if (root->child[cur] == nullptr) {
                return retVal;
            }
            root = root->child[cur];
        }
        retVal = true;

        return retVal;
    }
};
/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
```

</details>

<details><summary>Python3</summary>

```python
class Trie:
    def __init__(self):
        # word and prefix consist only of lowercase English letters.
        self.children = [None] * 26
        self.isEnd = False

    def searchPrefix(self, prefix: str) -> "Trie":
        retVal = self

        for ch in prefix:
            ch = ord(ch) - ord("a")
            if not retVal.children[ch]:
                retVal = None
                return retVal
            retVal = retVal.children[ch]

        return retVal

    def insert(self, word: str) -> None:
        node = self
        for ch in word:
            ch = ord(ch) - ord("a")
            if not node.children[ch]:
                node.children[ch] = Trie()
            node = node.children[ch]
        node.isEnd = True

    def search(self, word: str) -> bool:
        retVal = False

        node = self.searchPrefix(word)
        retVal = (node is not None) and (node.isEnd)

        return retVal

    def startsWith(self, prefix: str) -> bool:
        retVal = False

        retVal = self.searchPrefix(prefix) is not None

        return retVal

# Your Trie object will be instantiated and called as such:
# obj = Trie()
# obj.insert(word)
# param_2 = obj.search(word)
# param_3 = obj.startsWith(prefix)
```

</details>

## [211. Design Add and Search Words Data Structure](https://leetcode.com/problems/design-add-and-search-words-data-structure/)

- [Official](https://leetcode.cn/problems/design-add-and-search-words-data-structure/solutions/1053383/tian-jia-yu-sou-suo-dan-ci-shu-ju-jie-go-n4ud/)

<details><summary>Description</summary>

```text
Design a data structure that supports adding new words and finding if a string matches any previously added string.

Implement the WordDictionary class:
- WordDictionary()
  Initializes the object.
- void addWord(word)
  Adds word to the data structure, it can be matched later.
- bool search(word)
  Returns true if there is any string in the data structure that matches word or false otherwise.
  word may contain dots '.' where dots can be matched with any letter.

Example:
Input
["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
[[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
Output
[null,null,null,null,false,true,true,true]
Explanation
WordDictionary wordDictionary = new WordDictionary();
wordDictionary.addWord("bad");
wordDictionary.addWord("dad");
wordDictionary.addWord("mad");
wordDictionary.search("pad"); // return False
wordDictionary.search("bad"); // return True
wordDictionary.search(".ad"); // return True
wordDictionary.search("b.."); // return True

Constraints:
1 <= word.length <= 25
word in addWord consists of lowercase English letters.
word in search consist of '.' or lowercase English letters.
There will be at most 3 dots in word for search queries.
At most 10^4 calls will be made to addWord and search.
```

<details><summary>Hint</summary>

```text
1. You should be familiar with how a Trie works. If not, please work on this problem: Implement Trie (Prefix Tree) first.
```

</details>

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/design-add-and-search-words-data-structure/solutions/1440451/c-by-codee-3-nka1/
#define MAX_CHAR (26)  // word in addWord consists of lowercase English letters.
typedef struct WordDictionary {
    struct WordDictionary* child[MAX_CHAR];
    bool isEnd;
} WordDictionary;
WordDictionary* wordDictionaryCreate() {
    WordDictionary* pRetVal = (WordDictionary*)malloc(sizeof(WordDictionary));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal->child, 0, MAX_CHAR * sizeof(WordDictionary*));
    pRetVal->isEnd = false;

    return pRetVal;
}
void wordDictionaryAddWord(WordDictionary* obj, char* word) {
    int len = strlen(word);

    int ch;
    int i;
    for (i = 0; i < len; ++i) {
        ch = word[i] - 'a';
        if (obj->child[ch] != NULL) {
            obj = obj->child[ch];
            continue;
        }
        obj->child[ch] = (WordDictionary*)malloc(sizeof(WordDictionary));
        obj = obj->child[ch];
        memset(obj->child, 0, sizeof(obj->child));
        obj->isEnd = false;
    }

    obj->isEnd = true;
}
bool wordDictionarySearch(WordDictionary* obj, char* word) {
    bool retVal = false;

    if (obj == NULL) {
        return retVal;
    }

    int len = strlen(word);
    if (len == 0) {
        retVal = obj->isEnd;
        return retVal;
    }

    if (word[0] != '.') {
        retVal = wordDictionarySearch(obj->child[word[0] - 'a'], word + 1);
        return retVal;
    }

    int i;
    for (i = 0; i < MAX_CHAR; i++) {
        if (wordDictionarySearch(obj->child[i], word + 1)) {
            retVal = true;
            break;
        }
    }

    return retVal;
}
void wordDictionaryFree(WordDictionary* obj) {
    int i;
    for (i = 0; i < MAX_CHAR; i++) {
        if (obj->child[i]) {
            wordDictionaryFree(obj->child[i]);
        }
    }
    free(obj);
}
/**
 * Your WordDictionary struct will be instantiated and called as such:
 * WordDictionary* obj = wordDictionaryCreate();
 * wordDictionaryAddWord(obj, word);
 * bool param_2 = wordDictionarySearch(obj, word);
 * wordDictionaryFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
// https://leetcode.cn/problems/design-add-and-search-words-data-structure/solutions/1054681/fu-xue-ming-zhu-qian-zhui-shu-xiang-xi-r-rty2/
#define MAX_CHAR (26)  // word in addWord consists of lowercase English letters.
class TrieNode {
   public:
    vector<TrieNode*> child;
    bool isWord;
    TrieNode() : child(MAX_CHAR, nullptr), isWord(false){};
    ~TrieNode() {
        for (auto c : child) {
            delete c;
        }
    }
};
class WordDictionary {
   private:
    TrieNode* root;

   public:
    WordDictionary() {
        //
        root = new TrieNode();
    }
    ~WordDictionary() {
        //
        delete root;
    }
    void addWord(string word) {
        TrieNode* p = root;
        for (char c : word) {
            int i = c - 'a';
            if (!p->child[i]) p->child[i] = new TrieNode();
            p = p->child[i];
        }
        p->isWord = true;
    }
    bool search(string word) {
        bool retVal = match(word, root, 0);

        return retVal;
    }
    bool match(string& word, TrieNode* pRoot, int start) {
        bool retVal = false;

        if (pRoot == nullptr) {
            return retVal;
        }

        if (start == (int)word.size()) {
            retVal = pRoot->isWord;
            return retVal;
        }

        char c = word[start];
        if (c != '.') {
            retVal = match(word, pRoot->child[c - 'a'], start + 1);
            return retVal;
        }
        for (const auto& child : pRoot->child) {
            if (match(word, child, start + 1) == true) {
                retVal = true;
                break;
            }
        }

        return retVal;
    }
};
/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
```

</details>

<details><summary>Python3</summary>

```python
class TrieNode:
    def __init__(self):
        # word in addWord consists of lowercase English letters.
        self.letters = 26
        self.children = [None] * self.letters
        self.isEnd = False

    def insert(self, word: str) -> None:
        node = self
        for ch in word:
            ch = ord(ch) - ord('a')
            if not node.children[ch]:
                node.children[ch] = TrieNode()
            node = node.children[ch]
        node.isEnd = True


class WordDictionary:
    def __init__(self):
        self.trieRoot = TrieNode()

    def addWord(self, word: str) -> None:
        self.trieRoot.insert(word)

    def search(self, word: str) -> bool:
        retVal = False

        wordSize = len(word)

        def dfs(index: int, node: TrieNode) -> bool:
            retVal = False

            if index == wordSize:
                retVal = node.isEnd
                return retVal

            ch = word[index]
            if ch != '.':
                child = node.children[ord(ch) - ord('a')]
                if child is not None and dfs(index + 1, child):
                    retVal = True
            else:
                for child in node.children:
                    if child is not None and dfs(index + 1, child):
                        retVal = True
                        break

            return retVal

        retVal = dfs(0, self.trieRoot)

        return retVal


# Your WordDictionary object will be instantiated and called as such:
# obj = WordDictionary()
# obj.addWord(word)
# param_2 = obj.search(word)
```

</details>

## [212. Word Search II](https://leetcode.com/problems/word-search-ii/)

<details><summary>Description</summary>

```text
Given an m x n board of characters and a list of strings words, return all words on the board.

Each word must be constructed from letters of sequentially adjacent cells,
where adjacent cells are horizontally or vertically neighboring.
The same letter cell may not be used more than once in a word.
```

```text
Example 1:
Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
Output: ["eat","oath"]
```

```mermaid
graph TD
    subgraph words = oath, pea, eat, rain
        root((root)) --> w00((o)) --> w01((a)) --> w02((t)) --> w03((h)) --- str0[oath]
        root((root)) --> w10((p)) --> w11((e)) --> w12((a)) --- str1[pea]
        root((root)) --> w20((e)) --> w21((a)) --> w22((t)) --- str2[eat]
        root((root)) --> w30((r)) --> w31((a)) --> w32((i)) --> w33((n)) --- str3[rain]
    end
```

```text
Example 2:
Input: board = [["a","b"],["c","d"]], words = ["abcb"]
Output: []
```

```text
Constraints:
m == board.length
n == board[i].length
1 <= m, n <= 12
board[i][j] is a lowercase English letter.
1 <= words.length <= 3 * 10^4
1 <= words[i].length <= 10
words[i] consists of lowercase English letters.
All the strings of words are unique.
```

</details>

<details><summary>C</summary>

```c
// board[i][j] is a lowercase English letter.
#define TRIE_WIDTH      (26)
struct TrieNode {
    char* str;
    struct TrieNode* child[TRIE_WIDTH];
};
struct TrieNode* createNode() {
    struct TrieNode* pNew = (struct TrieNode*)calloc(1, sizeof(struct TrieNode));
    if (pNew == NULL) {
        perror("perror");
    }

    return pNew;
}
void freeNode(struct TrieNode* pRoot) {
    if (pRoot == NULL) {
        return;
    }

    int i;
    for (i=0; i<TRIE_WIDTH; ++i) {
        freeNode(pRoot->child[i]);
    }

    free(pRoot);
}
struct TrieNode* addNode(struct TrieNode* pRoot, char* pWord) {
    struct TrieNode* pCurrent = pRoot;

    int idx;
    int i;
    for (i=0; pWord[i]!='\0'; ++i) {
        idx = pWord[i] - 'a';
        if (pCurrent->child[idx] == NULL) {
            pCurrent->child[idx] = createNode();
        }
        pCurrent = pCurrent->child[idx];
    }
    pCurrent->str = pWord;

    return pRoot;
}
// Depth-First Search
#define VISITED     (-1)
void dfs(struct TrieNode* pRoot, char** board, int boardRow, int boardCol, int row, int col, char** retVal, int* returnSize) {
    // Exceed boundary
    if ((row == boardRow) || (row < 0)) {
        return;
    }
    else if ((col == boardCol) || (col < 0)) {
        return;
    }

    // Current board has been visited
    if (board[row][col] == VISITED) {
        return;
    }

    // This string path is not in the trie
    if ((pRoot->child[board[row][col] -'a']) == NULL) {
        return;
    }

    pRoot = pRoot->child[board[row][col] - 'a'];
    if (pRoot->str) {
        retVal[*returnSize] = pRoot->str;
        (*returnSize) += 1;
        pRoot->str = NULL;
    }

    char tmp = board[row][col];
    board[row][col] = VISITED;
    dfs(pRoot, board, boardRow, boardCol, row+1, col, retVal, returnSize);
    dfs(pRoot, board, boardRow, boardCol, row-1, col, retVal, returnSize);
    dfs(pRoot, board, boardRow, boardCol, row, col+1, retVal, returnSize);
    dfs(pRoot, board, boardRow, boardCol, row, col-1, retVal, returnSize);
    board[row][col] = tmp;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** findWords(char** board, int boardSize, int* boardColSize, char** words, int wordsSize, int* returnSize) {
    char** pRetVal = NULL;
    (*returnSize) = 0;

    pRetVal= malloc(sizeof(char*) * wordsSize);
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (sizeof(char*) * wordsSize));

    int i, j;

    struct TrieNode* pRoot = createNode();
    if (pRoot == NULL) {
        return pRetVal;
    }
    for (i=0; i<wordsSize; ++i) {
        pRoot = addNode(pRoot, words[i]);
    }

    for (i=0; i<boardSize; ++i) {
        for (j=0; j<boardColSize[i]; ++j) {
            dfs(pRoot, board, boardSize, boardColSize[i], i, j, pRetVal, returnSize);
        }
    }

    freeNode(pRoot);

    return pRetVal;
}
```

</details>

## [472. Concatenated Words](https://leetcode.com/problems/concatenated-words/)

- [Official](https://leetcode.com/problems/concatenated-words/solutions/2822170/concatenated-words/)
- [Official](https://leetcode.cn/problems/concatenated-words/solutions/1179021/lian-jie-ci-by-leetcode-solution-mj4d/)

<details><summary>Description</summary>

```text
Given an array of strings words (without duplicates), return all the concatenated words in the given list of words.

A concatenated word is defined as a string that is comprised entirely of at least two shorter words in the given array.

Example 1:
Input: words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]
Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats";
"dogcatsdog" can be concatenated by "dog", "cats" and "dog";
"ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".

Example 2:
Input: words = ["cat","dog","catdog"]
Output: ["catdog"]

Constraints:
1 <= words.length <= 10^4
1 <= words[i].length <= 30
words[i] consists of only lowercase English letters.
All the strings of words are unique.
1 <= sum(words[i].length) <= 10^5
```

</details>

<details><summary>C</summary>

```c
#define DYNAMIC_PROGRAMMING_SUBSTR (1)
#if (DYNAMIC_PROGRAMMING_SUBSTR)
// 1 <= words[i].length <= 30
#define MAX_LENGTH (30 + 1)
struct hashStruct {
    char key[MAX_LENGTH];
    int value;
    UT_hash_handle hh;
};
void freeAll(struct hashStruct* pFree) {
    struct hashStruct* current;
    struct hashStruct* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        HASH_DEL(pFree, current);
        free(current);
    }
}
#endif
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** findAllConcatenatedWordsInADict(char** words, int wordsSize, int* returnSize) {
    char** pRetVal = NULL;

    int i, j, k;

    //
    (*returnSize) = wordsSize;
    pRetVal = (char**)malloc((*returnSize) * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }

#if (DYNAMIC_PROGRAMMING_SUBSTR)
    //
    struct hashStruct* pWordsHashTable = NULL;
    struct hashStruct* pWord;
    for (i = 0; i < wordsSize; ++i) {
        pWord = NULL;
        HASH_FIND_STR(pWordsHashTable, words[i], pWord);
        pWord = (struct hashStruct*)malloc(sizeof(struct hashStruct));
        if (pWord == NULL) {
            perror("malloc");
            freeAll(pWordsHashTable);
            free(pRetVal);
            pRetVal = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        snprintf(pWord->key, MAX_LENGTH, "%s", words[i]);
        pWord->value = 1;
        HASH_ADD_STR(pWordsHashTable, key, pWord);
    }

    //
    int len;
    int* dp = NULL;
    char* buf = NULL;
    int bufSize = 0;
    int exist = 0;
    struct hashStruct* pFind;
    (*returnSize) = 0;
    for (i = 0; i < wordsSize; ++i) {
        len = strlen(words[i]);

        dp = (int*)malloc((len + 1) * sizeof(int));
        if (dp == NULL) {
            perror("malloc");
            freeAll(pWordsHashTable);
            free(pRetVal);
            pRetVal = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        memset(dp, 0, ((len + 1) * sizeof(int)));
        dp[0] = 1;

        for (j = 1; j <= len; ++j) {
            for (k = (j == len ? 1 : 0); k < j; ++k) {
                if (dp[j] == 1) {
                    break;
                }

                bufSize = j - k + 1;
                buf = (char*)malloc(bufSize * sizeof(char));
                if (buf == NULL) {
                    perror("malloc");
                    freeAll(pWordsHashTable);
                    free(dp);
                    dp = NULL;
                    free(pRetVal);
                    pRetVal = NULL;
                    (*returnSize) = 0;
                    return pRetVal;
                }
                memset(buf, 0, (bufSize * sizeof(char)));
                memcpy(buf, words[i] + k, ((bufSize - 1) * sizeof(char)));

                exist = 0;
                pFind = NULL;
                HASH_FIND_STR(pWordsHashTable, buf, pFind);
                if (pFind != NULL) {
                    exist = 1;
                }
                dp[j] = dp[k] & exist;

                free(buf);
                buf = NULL;
            }
        }

        if (dp[len] == 1) {
            pRetVal[(*returnSize)] = (char*)malloc((len + 1) * sizeof(char));
            if (pRetVal[(*returnSize)] == NULL) {
                perror("malloc");
                for (j = 0; j < (*returnSize); ++j) {
                    if (pRetVal[j]) {
                        free(pRetVal[j]);
                        pRetVal[j] = NULL;
                    }
                }
                freeAll(pWordsHashTable);
                free(dp);
                dp = NULL;
                free(pRetVal);
                pRetVal = NULL;
                (*returnSize) = 0;
                return pRetVal;
            }
            memset(pRetVal[(*returnSize)], 0, ((len + 1) * sizeof(char)));
            memcpy(pRetVal[(*returnSize)], words[i], ((len + 1) * sizeof(char)));
            (*returnSize)++;
        }

        free(dp);
        dp = NULL;
    }

    //
    freeAll(pWordsHashTable);
#else
    //
    int pWordLength;
    for (i = 0; i < (*returnSize); ++i) {
        pWordLength = strlen(words[i]) + 1;
        pRetVal[i] = (char*)malloc(pWordLength * sizeof(char));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                if (pRetVal[j]) {
                    free(pRetVal[j]);
                    pRetVal[j] = NULL;
                }
            }
            free(pRetVal);
            pRetVal = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        memset(pRetVal[i], 0, (pWordLength * sizeof(char)));
    }
#endif

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define DYNAMIC_PROGRAMMING_SUBSTR (0)
#define DYNAMIC_PROGRAMMING_TRIE (1)  // valgrind: definitely lost

   private:
#if (DYNAMIC_PROGRAMMING_SUBSTR)
#elif (DYNAMIC_PROGRAMMING_TRIE)
#define MAX_CHAR (26)  // words[i] consists of only lowercase English letters.

    struct trie {
        struct trie* arr[MAX_CHAR];
        bool end = false;
        trie() {
            memset(arr, 0, sizeof(arr));
            end = false;
        }
    };
    trie* root;

    void insert(string s) {
        trie* node = root;

        // inserting the string in reverse order as we will search from the end of the word while using DP.
        for (int i = s.length() - 1; i >= 0; --i) {
            if (node->arr[s[i] - 'a'] == NULL) {
                node->arr[s[i] - 'a'] = new trie();
            }
            node = node->arr[s[i] - 'a'];
        }
        node->end = true;
    }
#endif

   public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        vector<string> retVal;

#if (DYNAMIC_PROGRAMMING_SUBSTR)
        cout << "DYNAMIC_PROGRAMMING_SUBSTR\n";

        unordered_set<string> hashTable(words.begin(), words.end());
        for (auto word : words) {
            int len = word.length();
            vector<bool> dp(len + 1);
            dp[0] = true;

            for (int i = 1; i <= len; ++i) {
                for (int j = (i == len ? 1 : 0); j < i; ++j) {
                    if (dp[i] == true) {
                        break;
                    }
                    dp[i] = dp[j] && hashTable.count(word.substr(j, i - j));
                }
            }

            if (dp[len] == true) {
                retVal.push_back(word);
            }
        }
#elif (DYNAMIC_PROGRAMMING_TRIE)
        // https://leetcode.com/problems/concatenated-words/solutions/1401307/accepted-192ms-c-solution-using-dp-and-trie/
        cout << "DYNAMIC_PROGRAMMING_TRIE\n";

        sort(words.begin(), words.end(), [](const string& w1, const string& w2) {
            /* every word can be generated by concatinating smaller words only,
             * so smaller words will be processed and inserted into trie first
             */
            return (w1.size() < w2.size());
        });

        root = new trie();
        for (auto word : words) {
            int len = word.length();
            if (len == 0) {
                continue;
            }
            vector<bool> dp(len + 1, false);
            dp[0] = true;

            for (int i = 0; i < len; ++i) {
                trie* node = root;
                for (int j = i; j >= 0; --j) {
                    /* instead of keeping the smaller words into a map and
                     * searching in the map after doing substr() which is O(n) operation,
                     * trie is being used here to achieve constant time search operation of current suffix
                     */
                    if (node->arr[word[j] - 'a'] == NULL) {
                        break;
                    }

                    node = node->arr[word[j] - 'a'];
                    if (dp[j] && node->end) {
                        dp[i + 1] = true;
                        break;
                    }
                }
            }

            if (dp[len] == true) {
                retVal.push_back(word);
            }

            insert(word);
        }

        for (int i = 0; i < MAX_CHAR; ++i) {
            if (root->arr[i] != nullptr) {
                delete root->arr[i];
            }
        }
        delete root;
#endif

        return retVal;
    }
};
```

</details>

## [1268. Search Suggestions System](https://leetcode.com/problems/search-suggestions-system/)  1573

- [Official](https://leetcode.com/problems/search-suggestions-system/editorial)
- [Official](https://leetcode.cn/problems/search-suggestions-system/solutions/101822/suo-tui-jian-xi-tong-by-leetcode-solution/)

<details><summary>Description</summary>

```text
You are given an array of strings products and a string searchWord.

Design a system that suggests at most three product names from products after each character of searchWord is typed.
Suggested products should have common prefix with searchWord.
If there are more than three products with a common prefix return the three lexicographically minimums products.

Return a list of lists of the suggested products after each character of searchWord is typed.

Example 1:
Input: products = ["mobile","mouse","moneypot","monitor","mousepad"], searchWord = "mouse"
Output: [["mobile","moneypot","monitor"],["mobile","moneypot","monitor"],["mouse","mousepad"],
["mouse","mousepad"],["mouse","mousepad"]]
Explanation: products sorted lexicographically = ["mobile","moneypot","monitor","mouse","mousepad"].
After typing m and mo all products match and we show user ["mobile","moneypot","monitor"].
After typing mou, mous and mouse the system suggests ["mouse","mousepad"].

Example 2:
Input: products = ["havana"], searchWord = "havana"
Output: [["havana"],["havana"],["havana"],["havana"],["havana"],["havana"]]
Explanation: The only word "havana" will be always suggested while typing the search word.

Constraints:
1 <= products.length <= 1000
1 <= products[i].length <= 3000
1 <= sum(products[i].length) <= 2 * 10^4
All the strings of products are unique.
products[i] consists of lowercase English letters.
1 <= searchWord.length <= 1000
searchWord consists of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Brute force is a good choice because length of the string is ≤ 1000.
2. Binary search the answer.
3. Use Trie data structure to store the best three matching. Traverse the Trie.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareString(const void *str1, const void *str2) {
    // ascending order
    return strcmp(*(char **)str1, *(char **)str2);
}
void findProducts(char **ret, char **products, int productsSize, char *searchWord, int *size) {
    char *s = NULL;
    int i;
    for (i = 0; i < productsSize; ++i) {
        s = strstr(products[i], searchWord);
        if (s == products[i]) {
            ret[*size] = (char *)malloc((strlen(products[i]) + 1) * sizeof(char));
            strcpy(ret[(*size)++], products[i]);
        }
        if (*size == 3) {
            break;
        }
    }
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char ***suggestedProducts(char **products, int productsSize, char *searchWord, int *returnSize,
                          int **returnColumnSizes) {
    char ***pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    //
    int searchWordSize = strlen(searchWord);
    pRetVal = (char ***)malloc(searchWordSize * sizeof(char **));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    (*returnColumnSizes) = (int *)malloc(searchWordSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }

    qsort(products, productsSize, sizeof(char *), compareString);

    char tmp;
    int i, j;
    for (i = 0; i < searchWordSize; ++i) {
        pRetVal[i] = (char **)malloc(3 * sizeof(char *));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            return pRetVal;
        }

        tmp = 0;
        if (i + 1 < searchWordSize) {
            tmp = searchWord[i + 1];
            searchWord[i + 1] = 0;
        }

        (*returnColumnSizes)[i] = 0;
        findProducts(pRetVal[i], products, productsSize, searchWord, &(*returnColumnSizes)[i]);

        if (i + 1 < searchWordSize) {
            searchWord[i + 1] = tmp;
        }
    }
    (*returnSize) = searchWordSize;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
struct Trie {
    unordered_map<char, Trie*> child;
    priority_queue<string> words;
};
class Solution {
   private:
    void addWord(Trie* root, const string& product) {
        Trie* pCurrent = root;
        for (const char& c : product) {
            if (pCurrent->child.count(c) == 0) {
                pCurrent->child[c] = new Trie();
            }
            pCurrent = pCurrent->child[c];
            pCurrent->words.push(product);
            if (pCurrent->words.size() > 3) {
                pCurrent->words.pop();
            }
        }
    }
    void freeAll(Trie* pFree) {
        if (pFree == nullptr) {
            return;
        }

        for (int i = 0; i <= 26; i++) {
            freeAll(pFree->child['a' + i]);
        }

        delete pFree;
        pFree = nullptr;
    }

   public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        vector<vector<string>> retVal;

        //
        Trie* pRoot = new Trie();
        for (const string& product : products) {
            addWord(pRoot, product);
        }

        //
        Trie* pCurrent = pRoot;
        bool flag = false;
        for (const char& c : searchWord) {
            if ((flag == true) || (pCurrent->child.count(c) == 0)) {
                retVal.emplace_back();
                flag = true;
            } else {
                pCurrent = pCurrent->child[c];
                vector<string> selects;
                while (pCurrent->words.empty() == false) {
                    selects.push_back(pCurrent->words.top());
                    pCurrent->words.pop();
                }
                reverse(selects.begin(), selects.end());
                retVal.push_back(move(selects));
            }
        }

        //
        freeAll(pRoot);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Trie:
    def __init__(self):
        self.child = dict()
        self.words = list()


class Solution:
    def addWord(self, root, product) -> None:
        pCurrent = root
        for c in product:
            if c not in pCurrent.child:
                pCurrent.child[c] = Trie()
            pCurrent = pCurrent.child[c]
            pCurrent.words.append(product)
            pCurrent.words.sort()
            if len(pCurrent.words) > 3:
                pCurrent.words.pop()

    def suggestedProducts(self, products: List[str], searchWord: str) -> List[List[str]]:
        retVal = []

        #
        root = Trie()
        for product in products:
            self.addWord(root, product)

        #
        pCurrent = root
        flag = False
        for c in searchWord:
            if flag or c not in pCurrent.child:
                retVal.append(list())
                flag = True
            else:
                pCurrent = pCurrent.child[c]
                retVal.append(pCurrent.words)

        return retVal
```

</details>
