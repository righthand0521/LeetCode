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

- [Official](https://leetcode.cn/problems/word-search-ii/solutions/1000172/dan-ci-sou-suo-ii-by-leetcode-solution-7494/)

<details><summary>Description</summary>

```text
Given an m x n board of characters and a list of strings words, return all words on the board.

Each word must be constructed from letters of sequentially adjacent cells,
where adjacent cells are horizontally or vertically neighboring.
The same letter cell may not be used more than once in a word.

Example 1:
Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
Output: ["eat","oath"]

Example 2:
Input: board = [["a","b"],["c","d"]], words = ["abcb"]
Output: []

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

<details><summary>C++</summary>

```c++
class Solution {
   private:
    struct TrieNode {
        string word;
        unordered_map<char, TrieNode*> children;
        TrieNode() { this->word = ""; }
    };
    void insertTrie(TrieNode* root, const string& word) {
        TrieNode* node = root;
        for (auto c : word) {
            if (node->children.count(c) == 0) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->word = word;
    }

   public:
    bool dfs(vector<vector<char>>& board, int row, int col, TrieNode* root, set<string>& answer) {
        bool retVal = false;

        char ch = board[row][col];
        if (root->children.count(ch) == 0) {
            return retVal;
        }

        root = root->children[ch];
        if (root->word.size() > 0) {
            answer.insert(root->word);
        }

        board[row][col] = '#';
        int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int boardSize = board.size();
        int boardColSize = board[0].size();
        for (int i = 0; i < 4; ++i) {
            int x = row + dirs[i][0];
            int y = col + dirs[i][1];
            if ((x >= 0) && (x < boardSize) && (y >= 0) && (y < boardColSize)) {
                if (board[x][y] != '#') {
                    dfs(board, x, y, root, answer);
                }
            }
        }
        board[row][col] = ch;
        retVal = true;

        return retVal;
    }
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> retVal;

        TrieNode* root = new TrieNode();
        for (auto& word : words) {
            insertTrie(root, word);
        }

        set<string> answer;
        int boardSize = board.size();
        int boardColSize = board[0].size();
        for (int row = 0; row < boardSize; ++row) {
            for (int col = 0; col < boardColSize; ++col) {
                dfs(board, row, col, root, answer);
            }
        }
        for (auto& word : answer) {
            retVal.emplace_back(word);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Trie:
    def __init__(self) -> None:
        self.children = defaultdict(Trie)
        self.word = ""

    def insert(self, word: str) -> None:
        cur = self
        for c in word:
            cur = cur.children[c]
        cur.is_word = True
        cur.word = word


class Solution:
    def dfs(self, board: List[List[str]], now: Trie, row: int, col: int, answer: set) -> None:
        if board[row][col] not in now.children:
            return

        ch = board[row][col]
        now = now.children[ch]
        if now.word != "":
            answer.add(now.word)

        board[row][col] = "#"
        boardSize = len(board)
        boardColSize = len(board[0])
        for i2, j2 in [(row + 1, col), (row - 1, col), (row, col + 1), (row, col - 1)]:
            if (0 <= i2 < boardSize) and (0 <= j2 < boardColSize):
                self.dfs(board, now, i2, j2, answer)
        board[row][col] = ch

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        retVal = []

        trie = Trie()
        for word in words:
            trie.insert(word)

        answer = set()
        boardSize = len(board)
        boardColSize = len(board[0])
        for row in range(boardSize):
            for col in range(boardColSize):
                self.dfs(board, trie, row, col, answer)
        retVal = list(answer)

        return retVal
```

</details>

## [386. Lexicographical Numbers](https://leetcode.com/problems/lexicographical-numbers/)

- [Official](https://leetcode.com/problems/lexicographical-numbers/editorial/)
- [Official](https://leetcode.cn/problems/lexicographical-numbers/solutions/1428281/zi-dian-xu-pai-shu-by-leetcode-solution-98mz/)

<details><summary>Description</summary>

```text
Given an integer n, return all the numbers in the range [1, n] sorted in lexicographical order.

You must write an algorithm that runs in O(n) time and uses O(1) extra space.

Example 1:
Input: n = 13
Output: [1,10,11,12,13,2,3,4,5,6,7,8,9]

Example 2:
Input: n = 2
Output: [1,2]

Constraints:
1 <= n <= 5 * 10^4
```

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *lexicalOrder(int n, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int *)malloc(n * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (n * sizeof(int)));

    int currentNumber = 1;
    int i;
    for (i = 0; i < n; ++i) {
        pRetVal[(*returnSize)++] = currentNumber;

        if (currentNumber * 10 <= n) {
            currentNumber *= 10;
            continue;
        }

        while ((currentNumber % 10) == 9 || (currentNumber >= n)) {
            currentNumber /= 10;
        }
        currentNumber += 1;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> lexicalOrder(int n) {
        vector<int> retVal;

        int currentNumber = 1;
        for (int i = 0; i < n; ++i) {
            retVal.emplace_back(currentNumber);

            if (currentNumber * 10 <= n) {
                currentNumber *= 10;
                continue;
            }

            while ((currentNumber % 10) == 9 || (currentNumber >= n)) {
                currentNumber /= 10;
            }
            currentNumber += 1;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def lexicalOrder(self, n: int) -> List[int]:
        retVal = []

        currentNumber = 1
        for _ in range(n):
            retVal.append(currentNumber)

            if currentNumber * 10 <= n:
                currentNumber *= 10
                continue

            while (currentNumber % 10) == 9 or (currentNumber >= n):
                currentNumber //= 10
            currentNumber += 1

        return retVal
```

</details>

## [440. K-th Smallest in Lexicographical Order](https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/)

- [Official](https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/editorial/)
- [Official](https://leetcode.cn/problems/k-th-smallest-in-lexicographical-order/solutions/1358635/zi-dian-xu-de-di-kxiao-shu-zi-by-leetcod-bfy0/)

<details><summary>Description</summary>

```text
Given two integers n and k, return the kth lexicographically smallest integer in the range [1, n].

Example 1:
Input: n = 13, k = 2
Output: 10
Explanation: The lexicographical order is [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9],
so the second smallest number is 10.

Example 2:
Input: n = 1, k = 1
Output: 1

Constraints:
1 <= k <= n <= 10^9
```

</details>

<details><summary>C</summary>

```c
// To count how many numbers exist between prefix1 and prefix2
int countSteps(int n, long prefix1, long prefix2) {
    int retVal = 0;

    while (prefix1 <= n) {
        retVal += fmin((long)(n + 1), prefix2) - prefix1;
        prefix1 *= 10;
        prefix2 *= 10;
    }

    return retVal;
}
int findKthNumber(int n, int k) {
    int retVal = 1;

    int step;
    k--;
    while (k > 0) {
        step = countSteps(n, retVal, retVal + 1);

        // If the steps are less than or equal to k, we skip this prefix's subtree
        if (step <= k) {
            // Move to the next prefix and decrease k by the number of steps we skip
            retVal++;
            k -= step;
        } else {
            // Move to the next level of the tree and decrement k by 1
            retVal *= 10;
            k--;
        }
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    // To count how many numbers exist between prefix1 and prefix2
    int countSteps(int n, long prefix1, long prefix2) {
        int retVal = 0;

        while (prefix1 <= n) {
            retVal += min((long)(n + 1), prefix2) - prefix1;
            prefix1 *= 10;
            prefix2 *= 10;
        }

        return retVal;
    }

   public:
    int findKthNumber(int n, int k) {
        int retVal = 1;

        k--;
        while (k > 0) {
            int step = countSteps(n, retVal, retVal + 1);

            // If the steps are less than or equal to k, we skip this prefix's subtree
            if (step <= k) {
                // Move to the next prefix and decrease k by the number of steps we skip
                retVal++;
                k -= step;
            } else {
                // Move to the next level of the tree and decrement k by 1
                retVal *= 10;
                k--;
            }
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    # To count how many numbers exist between prefix1 and prefix2
    def countSteps(self, n: int, prefix1: int, prefix2: int) -> int:
        retVal = 0

        while prefix1 <= n:
            retVal += min(n + 1, prefix2) - prefix1
            prefix1 *= 10
            prefix2 *= 10

        return retVal

    def findKthNumber(self, n: int, k: int) -> int:
        retVal = 1

        k -= 1
        while k > 0:
            step = self.countSteps(n, retVal, retVal + 1)

            # If the steps are less than or equal to k, we skip this prefix's subtree
            if step <= k:
                # Move to the next prefix and decrease k by the number of steps we skip
                retVal += 1
                k -= step
            else:
                # Move to the next level of the tree and decrement k by 1
                retVal *= 10
                k -= 1

        return retVal
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

## [1233. Remove Sub-Folders from the Filesystem](https://leetcode.com/problems/remove-sub-folders-from-the-filesystem/)  1544

- [Official](https://leetcode.com/problems/remove-sub-folders-from-the-filesystem/editorial/)
- [Official](https://leetcode.cn/problems/remove-sub-folders-from-the-filesystem/solutions/2097563/shan-chu-zi-wen-jian-jia-by-leetcode-sol-0x8d/)

<details><summary>Description</summary>

```text
Given a list of folders folder, return the folders after removing all sub-folders in those folders.
You may return the answer in any order.

If a folder[i] is located within another folder[j], it is called a sub-folder of it.
A sub-folder of folder[j] must start with folder[j], followed by a "/".
For example, "/a/b" is a sub-folder of "/a", but "/b" is not a sub-folder of "/a/b/c".

The format of a path is one or more concatenated strings of the form:
'/' followed by one or more lowercase English letters.
- For example, "/leetcode" and "/leetcode/problems" are valid paths while an empty string and "/" are not.

Example 1:
Input: folder = ["/a","/a/b","/c/d","/c/d/e","/c/f"]
Output: ["/a","/c/d","/c/f"]
Explanation: Folders "/a/b" is a subfolder of "/a" and "/c/d/e" is inside of folder "/c/d" in our filesystem.

Example 2:
Input: folder = ["/a","/a/b/c","/a/b/d"]
Output: ["/a"]
Explanation: Folders "/a/b/c" and "/a/b/d" will be removed because they are subfolders of "/a".

Example 3:
Input: folder = ["/a/b/c","/a/b/ca","/a/b/d"]
Output: ["/a/b/c","/a/b/ca","/a/b/d"]

Constraints:
1 <= folder.length <= 4 * 10^4
2 <= folder[i].length <= 100
folder[i] contains only lowercase letters and '/'.
folder[i] always starts with the character '/'.
Each folder name is unique.
```

<details><summary>Hint</summary>

```text
1. Sort the folders lexicographically.
2. Insert the current element in an array and then loop until we get rid of all of their subfolders,
   repeat this until no element is left.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareString(const void* str1, const void* str2) {
    // ascending order
    return strcmp(*(char**)str1, *(char**)str2);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** removeSubfolders(char** folder, int folderSize, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (char**)malloc(folderSize * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    // Sort the folders alphabetically
    qsort(folder, folderSize, sizeof(char*), compareString);

    // Initialize the retVal vector and add the first folder
    pRetVal[(*returnSize)++] = folder[0];

    // Iterate through each folder and check if it's a sub-folder of the last added folder in the retVal
    int lastFolderSize;
    int i;
    for (i = 1; i < folderSize; ++i) {
        lastFolderSize = strlen(pRetVal[(*returnSize) - 1]);
        if (lastFolderSize < strlen(folder[i])) {
            if (strncmp(pRetVal[(*returnSize) - 1], folder[i], lastFolderSize) == 0) {
                if (folder[i][lastFolderSize] == '/') {
                    continue;
                }
            }
        }
        pRetVal[(*returnSize)++] = folder[i];
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<string> removeSubfolders(vector<string>& folder) {
        vector<string> retVal;

        // Sort the folders alphabetically
        sort(folder.begin(), folder.end());

        // Initialize the retVal vector and add the first folder
        retVal.push_back(folder[0]);

        // Iterate through each folder and check if it's a sub-folder of the last added folder in the retVal
        int folderSize = folder.size();
        for (int i = 1; i < folderSize; i++) {
            string lastFolder = retVal.back();
            lastFolder += '/';

            // Check if the current folder starts with the last added folder path
            int lastFolderSize = lastFolder.size();
            if (folder[i].compare(0, lastFolderSize, lastFolder) != 0) {
                retVal.push_back(folder[i]);
            }
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def removeSubfolders(self, folder: List[str]) -> List[str]:
        retVal = []

        # Sort the folders alphabetically
        folder.sort()

        # Initialize the retVal list and add the first folder
        retVal = [folder[0]]

        # Iterate through each folder and check if it's a sub-folder of the last added folder in the retVal
        folderSize = len(folder)
        for i in range(1, folderSize):
            lastFolder = retVal[-1]
            lastFolder += "/"

            # Check if the current folder starts with the last added folder path
            if not folder[i].startswith(lastFolder):
                retVal.append(folder[i])

        return retVal
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

## [1948. Delete Duplicate Folders in System](https://leetcode.com/problems/delete-duplicate-folders-in-system/)  2533

- [Official](https://leetcode.com/problems/delete-duplicate-folders-in-system/editorial/)
- [Official](https://leetcode.cn/problems/delete-duplicate-folders-in-system/solutions/895642/shan-chu-xi-tong-zhong-de-zhong-fu-wen-j-ic32/)

<details><summary>Description</summary>

```text
Due to a bug, there are many duplicate folders in a file system.
You are given a 2D array paths, where paths[i] is an array
representing an absolute path to the ith folder in the file system.
- For example, ["one", "two", "three"] represents the path "/one/two/three".

Two folders (not necessarily on the same level) are identical
if they contain the same non-empty set of identical subfolders and underlying subfolder structure.
The folders do not need to be at the root level to be identical.
If two or more folders are identical, then mark the folders as well as all their subfolders.
- For example, folders "/a" and "/b" in the file structure below are identical.
  They (as well as their subfolders) should all be marked:
  - /a
  - /a/x
  - /a/x/y
  - /a/z
  - /b
  - /b/x
  - /b/x/y
  - /b/z
- However, if the file structure also included the path "/b/w", then the folders "/a" and "/b" would not be identical.
  Note that "/a/x" and "/b/x" would still be considered identical even with the added folder.

Once all the identical folders and their subfolders have been marked, the file system will delete all of them.
The file system only runs the deletion once,
so any folders that become identical after the initial deletion are not deleted.

Return the 2D array ans containing the paths of the remaining folders after deleting all the marked folders.
The paths may be returned in any order.

Example 1:
   /
 / | \
a  c  d
|  |  |
b  b  a
Input: paths = [["a"],["c"],["d"],["a","b"],["c","b"],["d","a"]]
Output: [["d"],["d","a"]]
Explanation:
The file structure is as shown.
Folders "/a" and "/c" (and their subfolders) are marked for deletion because they both contain an empty
folder named "b".

Example 2:
   /
 / | \
a  c  w
|  |  |
b  b  y
|
x
|
y
Input: paths = [["a"],["c"],["a","b"],["c","b"],["a","b","x"],["a","b","x","y"],["w"],["w","y"]]
Output: [["c"],["c","b"],["a"],["a","b"]]
Explanation:
The file structure is as shown.
Folders "/a/b/x" and "/w" (and their subfolders) are marked for deletion
because they both contain an empty folder named "y".
Note that folders "/a" and "/c" are identical after the deletion,
but they are not deleted because they were not marked beforehand.

Example 3:
  /
 / \
a   c
|   |
b   d
Input: paths = [["a","b"],["c","d"],["c"],["a"]]
Output: [["c"],["c","d"],["a"],["a","b"]]
Explanation:
All folders are unique in the file system.
Note that the returned array can be in a different order as the order does not matter.

Constraints:
1 <= paths.length <= 2 * 10^4
1 <= paths[i].length <= 500
1 <= paths[i][j].length <= 10
1 <= sum(paths[i][j].length) <= 2 * 10^5
path[i][j] consists of lowercase English letters.
No two paths lead to the same folder.
For any folder not at the root level, its parent folder will also be in the input.
```

<details><summary>Hint</summary>

```text
1. Can we use a trie to build the folder structure?
2. Can we utilize hashing to hash the folder structures?
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** deleteDuplicateFolder(char*** paths, int pathsSize, int* pathsColSize, int* returnSize,
                              int** returnColumnSizes) {
    char*** pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    // TODO: Delete Duplicate Folders in System

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
struct Trie {
    string serial;                          // current node structure's serialized representation
    unordered_map<string, Trie*> children;  // current node's child nodes
};
class Solution {
   private:
    // post-order traversal based on depth-first search, calculate the serialized representation of each node structure
    void construct(Trie* node, unordered_map<string, int>& frequency) {
        // if it is a leaf node, then the serialization is represented as an empty string, and no operation is required.
        if (node->children.empty()) {
            return;
        }

        // if it is not a leaf node,
        // the serialization representation of the child node structure needs to be calculated first.
        vector<string> v;
        for (const auto& [folder, child] : node->children) {
            construct(child, frequency);
            v.push_back(folder + "(" + child->serial + ")");
        }

        // to prevent issues with order, sorting is needed
        sort(v.begin(), v.end());
        for (string& s : v) {
            node->serial += move(s);
        }

        // add to hash table
        ++frequency[node->serial];
    };
    void operate(Trie* node, unordered_map<string, int>& frequency, vector<string>& path,
                 vector<vector<string>>& retVal) {
        // if the serialization appears more than once in the hash table, it needs to be deleted.
        if (frequency[node->serial] > 1) {
            return;
        }

        // otherwise add the path to the answer
        if (path.empty() == false) {
            retVal.push_back(path);
        }

        for (const auto& [folder, child] : node->children) {
            path.push_back(folder);
            operate(child, frequency, path, retVal);
            path.pop_back();
        }
    };

   public:
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& paths) {
        vector<vector<string>> retVal;

        // root node
        Trie* root = new Trie();
        for (const vector<string>& path : paths) {
            Trie* current = root;
            for (const string& node : path) {
                if (!current->children.count(node)) {
                    current->children[node] = new Trie();
                }
                current = current->children[node];
            }
        }

        // hash table records the occurrence times of each serialized representation
        unordered_map<string, int> frequency;
        construct(root, frequency);

        // record the path from the root node to the current node.
        vector<string> path;
        operate(root, frequency, path, retVal);

        // free memory
        for (const auto& [folder, child] : root->children) {
            delete child;
        }
        delete root;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Trie:
    serial: str = ""  # current node structure's serialized representation
    children: dict  # current node's child nodes

    def __init__(self):
        self.children = dict()


class Solution:
    # post-order traversal based on depth-first search, calculate the serialized representation of each node structure
    def construct(self, node: Trie, frequency: Counter) -> None:
        # if it is a leaf node, then the serialization is represented as an empty string, and no operation is required.
        if not node.children:
            return

        # if it is not a leaf node, the serialization representation of the child node structure needs to be calculated first.
        v = list()
        for folder, child in node.children.items():
            self.construct(child, frequency)
            v.append(folder + "(" + child.serial + ")")

        # to prevent issues with order, sorting is needed
        v.sort()
        node.serial = "".join(v)

        # add to hash table
        frequency[node.serial] += 1

    def operate(self, node: Trie, frequency: Counter, path: List[str], retVal: List[List[str]]) -> None:
        # if the serialization appears more than once in the hash table, it needs to be deleted.
        if frequency[node.serial] > 1:
            return

        # otherwise add the path to the answer
        if path:
            retVal.append(path[:])

        for folder, child in node.children.items():
            path.append(folder)
            self.operate(child, frequency, path, retVal)
            path.pop()

    def deleteDuplicateFolder(self, paths: List[List[str]]) -> List[List[str]]:
        retVal = []

        # root node
        root = Trie()
        for path in paths:
            current = root
            for node in path:
                if node not in current.children:
                    current.children[node] = Trie()
                current = current.children[node]

        # hash table records the occurrence times of each serialized representation
        frequency = Counter()

        self.construct(root, frequency)

        path = list()  # record the path from the root node to the current node.
        self.operate(root, frequency, path, retVal)

        return retVal
```

</details>

## [2416. Sum of Prefix Scores of Strings](https://leetcode.com/problems/sum-of-prefix-scores-of-strings/)  1725

- [Official](https://leetcode.com/problems/sum-of-prefix-scores-of-strings/editorial/)

<details><summary>Description</summary>

```text
You are given an array words of size n consisting of non-empty strings.

We define the score of a string word as the number of strings words[i] such that word is a prefix of words[i].
- For example, if words = ["a", "ab", "abc", "cab"], then the score of "ab" is 2,
  since "ab" is a prefix of both "ab" and "abc".

Return an array answer of size n where answer[i] is the sum of scores of every non-empty prefix of words[i].

Note that a string is considered as a prefix of itself.

Example 1:
Input: words = ["abc","ab","bc","b"]
Output: [5,4,3,2]
Explanation: The answer for each string is the following:
- "abc" has 3 prefixes: "a", "ab", and "abc".
- There are 2 strings with the prefix "a", 2 strings with the prefix "ab", and 1 string with the prefix "abc".
The total is answer[0] = 2 + 2 + 1 = 5.
- "ab" has 2 prefixes: "a" and "ab".
- There are 2 strings with the prefix "a", and 2 strings with the prefix "ab".
The total is answer[1] = 2 + 2 = 4.
- "bc" has 2 prefixes: "b" and "bc".
- There are 2 strings with the prefix "b", and 1 string with the prefix "bc".
The total is answer[2] = 2 + 1 = 3.
- "b" has 1 prefix: "b".
- There are 2 strings with the prefix "b".
The total is answer[3] = 2.

Example 2:
Input: words = ["abcd"]
Output: [4]
Explanation:
"abcd" has 4 prefixes: "a", "ab", "abc", and "abcd".
Each prefix has a score of one, so the total is answer[0] = 1 + 1 + 1 + 1 = 4.

Constraints:
1 <= words.length <= 1000
1 <= words[i].length <= 1000
words[i] consists of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. What data structure will allow you to efficiently keep track of the score of each prefix?
2. Use a Trie. Insert all the words into it,
   and keep a counter at each node that will tell you how many times we have visited each prefix.
```

</details>

</details>

<details><summary>C</summary>

```c
#ifndef TREE_NODE_H
#define TREE_NODE_H

#define TRIE_WIDTH (26)  // words[i] consists of lowercase English letters.
typedef struct Trie {
    struct Trie* children[TRIE_WIDTH];
    int score;
} Trie;

Trie* createTrie() {
    Trie* pRetVal = NULL;

    pRetVal = (Trie*)malloc(sizeof(Trie));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal->children, 0, sizeof(pRetVal->children));
    pRetVal->score = 0;

    return pRetVal;
}
void insert(Trie* pObj, char* word) {
    int idx;
    int wordsSize = strlen(word);
    int i;
    for (i = 0; i < wordsSize; i++) {
        idx = word[i] - 'a';
        if (pObj->children[idx] == NULL) {
            pObj->children[idx] = createTrie();
            if (pObj->children[idx] == NULL) {
                perror("malloc");
                return;
            }
        }
        pObj = pObj->children[idx];
        pObj->score++;
    }
}
void freeTrie(Trie* pObj) {
    int i;
    for (i = 0; i < TRIE_WIDTH; i++) {
        if (pObj->children[i]) {
            freeTrie(pObj->children[i]);
            pObj->children[i] = NULL;
        }
    }
    free(pObj);
    pObj = NULL;
}

#endif  // TREE_NODE_H
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sumPrefixScores(char** words, int wordsSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;
    int i, j;

    pRetVal = (int*)malloc(wordsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (wordsSize * sizeof(int)));
    (*returnSize) = wordsSize;

    Trie* pRoot = createTrie();
    if (pRoot == NULL) {
        perror("malloc");
        return pRetVal;
    }
    for (i = 0; i < wordsSize; i++) {
        insert(pRoot, words[i]);
    }

    int idx, wordSize;
    Trie* pCurrent = pRoot;
    for (i = 0; i < wordsSize; ++i) {
        pCurrent = pRoot;
        wordSize = strlen(words[i]);
        for (j = 0; j < wordSize; j++) {
            idx = words[i][j] - 'a';
            pCurrent = pCurrent->children[idx];
            pRetVal[i] += pCurrent->score;
        }
    }

    freeTrie(pRoot);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
struct TrieNode {
    TrieNode* next[26] = {};  // words[i] consists of lowercase English letters.
    int cnt = 0;
};
class Solution {
    TrieNode root;

   public:
    void insert(string word) {
        auto node = &root;
        for (char c : word) {
            if (node->next[c - 'a'] == nullptr) {
                node->next[c - 'a'] = new TrieNode();
            }
            node->next[c - 'a']->cnt++;
            node = node->next[c - 'a'];
        }
    }
    int count(string s) {
        int retVal = 0;

        auto node = &root;
        for (char c : s) {
            retVal += node->next[c - 'a']->cnt;
            node = node->next[c - 'a'];
        }

        return retVal;
    }
    vector<int> sumPrefixScores(vector<string>& words) {
        vector<int> retVal;

        int wordsSize = words.size();

        for (int i = 0; i < wordsSize; i++) {
            insert(words[i]);
        }

        retVal.resize(wordsSize, 0);
        for (int i = 0; i < wordsSize; i++) {
            retVal[i] = count(words[i]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class TrieNode:
    def __init__(self) -> None:
        # words[i] consists of lowercase English letters.
        self.next = [None] * 26
        self.cnt = 0


class Solution:
    def __init__(self) -> None:
        self.root = TrieNode()

    def insert(self, word: str) -> None:
        node = self.root
        for c in word:
            if node.next[ord(c) - ord("a")] is None:
                node.next[ord(c) - ord("a")] = TrieNode()

            node.next[ord(c) - ord("a")].cnt += 1
            node = node.next[ord(c) - ord("a")]

    def count(self, s: str) -> int:
        retVal = 0

        node = self.root
        for c in s:
            retVal += node.next[ord(c) - ord("a")].cnt
            node = node.next[ord(c) - ord("a")]

        return retVal

    def sumPrefixScores(self, words: List[str]) -> List[int]:
        retVal = []

        wordsSize = len(words)

        for i in range(wordsSize):
            self.insert(words[i])

        retVal = [0] * wordsSize
        for i in range(wordsSize):
            retVal[i] = self.count(words[i])

        return retVal
```

</details>

## [3043. Find the Length of the Longest Common Prefix](https://leetcode.com/problems/find-the-length-of-the-longest-common-prefix/)  1688

- [Official](https://leetcode.com/problems/find-the-length-of-the-longest-common-prefix/editorial/)

<details><summary>Description</summary>

```text
You are given two arrays with positive integers arr1 and arr2.

A prefix of a positive integer is an integer formed by one or more of its digits, starting from its leftmost digit.
For example, 123 is a prefix of the integer 12345, while 234 is not.

A common prefix of two integers a and b is an integer c, such that c is a prefix of both a and b.
For example, 5655359 and 56554 have a common prefix 565 while 1223 and 43456 do not have a common prefix.

You need to find the length of the longest common prefix between all pairs of integers (x, y)
such that x belongs to arr1 and y belongs to arr2.

Return the length of the longest common prefix among all pairs. If no common prefix exists among them, return 0.

Example 1:
Input: arr1 = [1,10,100], arr2 = [1000]
Output: 3
Explanation: There are 3 pairs (arr1[i], arr2[j]):
- The longest common prefix of (1, 1000) is 1.
- The longest common prefix of (10, 1000) is 10.
- The longest common prefix of (100, 1000) is 100.
The longest common prefix is 100 with a length of 3.

Example 2:
Input: arr1 = [1,2,3], arr2 = [4,4,4]
Output: 0
Explanation: There exists no common prefix for any pair (arr1[i], arr2[j]), hence we return 0.
Note that common prefixes between elements of the same array do not count.

Constraints:
1 <= arr1.length, arr2.length <= 5 * 10^4
1 <= arr1[i], arr2[i] <= 10^8
```

<details><summary>Hint</summary>

```text
1. Put all the possible prefixes of each element in arr1 into a HashSet.
2. For all the possible prefixes of each element in arr2, check if it exists in the HashSet.
```

</details>

</details>

<details><summary>C</summary>

```c
#ifndef TREE_NODE_H
#define TREE_NODE_H

#define TRIE_WIDTH (10)  // Each node has up to 10 possible children (digits 0-9)
struct TrieNode {
    struct TrieNode* children[TRIE_WIDTH];
};
struct TrieNode* createNode() {
    struct TrieNode* pNew = (struct TrieNode*)calloc(1, sizeof(struct TrieNode));
    if (pNew == NULL) {
        perror("perror");
        return pNew;
    }

    int i;
    for (i = 0; i < TRIE_WIDTH; ++i) {
        pNew->children[i] = NULL;
    }

    return pNew;
}
void freeNode(struct TrieNode* pRoot) {
    if (pRoot == NULL) {
        return;
    }

    int i;
    for (i = 0; i < TRIE_WIDTH; ++i) {
        freeNode(pRoot->children[i]);
    }

    free(pRoot);
}
struct TrieNode* addNode(struct TrieNode* pRoot, int num) {
    struct TrieNode* pCurrent = pRoot;

    char numStr[8 + 4];  // 1 <= arr1[i], arr2[i] <= 10^8
    memset(numStr, 0, sizeof(numStr));
    snprintf(numStr, sizeof(numStr), "%d", num);
    int numStrSize = strlen(numStr);

    int idx;
    int i;
    for (i = 0; i < numStrSize; ++i) {
        idx = numStr[i] - '0';
        if (pCurrent->children[idx] == NULL) {
            pCurrent->children[idx] = createNode();
        }
        pCurrent = pCurrent->children[idx];
    }

    return pRoot;
}
int findLongestPrefix(struct TrieNode* pRoot, int num) {
    int retVal = 0;

    struct TrieNode* pCurrent = pRoot;

    char numStr[8 + 4];  // 1 <= arr1[i], arr2[i] <= 10^8
    memset(numStr, 0, sizeof(numStr));
    snprintf(numStr, sizeof(numStr), "%d", num);
    int numStrSize = strlen(numStr);

    int idx;
    int i;
    for (i = 0; i < numStrSize; ++i) {
        idx = numStr[i] - '0';
        if (pCurrent->children[idx]) {
            // Increase length if the current digit matches
            retVal++;
            pCurrent = pCurrent->children[idx];
        } else {
            // Stop if no match for the current digit
            break;
        }
    }

    return retVal;
}

#endif  // TREE_NODE_H
int longestCommonPrefix(int* arr1, int arr1Size, int* arr2, int arr2Size) {
    int retVal = 0;

    struct TrieNode* pObj = createNode();
    if (pObj == NULL) {
        return retVal;
    }

    // Step 1: Insert all numbers from arr1 into the Trie
    for (int i = 0; i < arr1Size; ++i) {
        pObj = addNode(pObj, arr1[i]);
    }

    // Step 2: Find the longest prefix match for each number in arr2
    int len;
    for (int i = 0; i < arr2Size; ++i) {
        len = findLongestPrefix(pObj, arr2[i]);
        retVal = fmax(retVal, len);
    }

    freeNode(pObj);
    pObj = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class TrieNode {
   public:
    TrieNode* children[10];  // Each node has up to 10 possible children (digits 0-9)

    TrieNode() {
        for (int i = 0; i < 10; ++i) {
            children[i] = nullptr;
        }
    }
    ~TrieNode() {
        for (int i = 0; i < 10; ++i) {
            delete children[i];
        }
    }
};
class Trie {
   public:
    TrieNode* root;

    Trie() {
        //
        root = new TrieNode();
    }
    ~Trie() {
        //
        delete root;
    }

    void insert(int num) {
        TrieNode* node = root;

        string numStr = to_string(num);
        for (char digit : numStr) {
            int idx = digit - '0';
            if (node->children[idx] == nullptr) {
                node->children[idx] = new TrieNode();
            }
            node = node->children[idx];
        }
    }
    int findLongestPrefix(int num) {
        int retVal = 0;

        TrieNode* node = root;
        string numStr = to_string(num);
        for (char digit : numStr) {
            int idx = digit - '0';
            if (node->children[idx]) {
                // Increase length if the current digit matches
                retVal++;
                node = node->children[idx];
            } else {
                // Stop if no match for the current digit
                break;
            }
        }

        return retVal;
    }
};
class Solution {
   public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        int retVal = 0;

        Trie trie;

        // Step 1: Insert all numbers from arr1 into the Trie
        for (int num : arr1) {
            trie.insert(num);
        }

        // Step 2: Find the longest prefix match for each number in arr2
        for (int num : arr2) {
            int len = trie.findLongestPrefix(num);
            retVal = max(retVal, len);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class TrieNode:
    def __init__(self):
        # Each node has up to 10 possible children (digits 0-9)
        self.children = [None] * 10


class Trie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, num) -> None:
        node = self.root
        numStr = str(num)
        for digit in numStr:
            idx = int(digit)
            if not node.children[idx]:
                node.children[idx] = TrieNode()
            node = node.children[idx]

    def findLongestPrefix(self, num) -> int:
        retVal = 0

        node = self.root
        numStr = str(num)
        for digit in numStr:
            idx = int(digit)
            if node.children[idx]:
                # Increase length if the current digit matches
                retVal += 1
                node = node.children[idx]
            else:
                # Stop if no match for the current digit
                break

        return retVal


class Solution:
    def longestCommonPrefix(self, arr1: List[int], arr2: List[int]) -> int:
        retVal = 0

        trie = Trie()

        # Step 1: Insert all numbers from arr1 into the Trie
        for num in arr1:
            trie.insert(num)

        # Step 2: Find the longest prefix match for each number in arr2
        for num in arr2:
            len = trie.findLongestPrefix(num)
            retVal = max(retVal, len)

        return retVal
```

</details>
