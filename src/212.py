import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop


def logging_setting():
    LOG_LEVEL = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt='%Y/%m/%d %H:%M:%S')


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


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for board, words in zip([[["o", "a", "a", "n"], ["e", "t", "a", "e"], ["i", "h", "k", "r"], ["i", "f", "l", "v"]],
                                 [["a", "b"], ["c", "d"]]],
                                [["oath", "pea", "eat", "rain"],
                                 ["abcb"]]):
            # /* Example
            #  *  Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
            #  *  Output: ["eat","oath"]
            #  *
            #  *  Input: board = [["a","b"],["c","d"]], words = ["abcb"]
            #  *  Output: []
            #  */
            logging.info("Input: board = %s, words = %s", board, words)

            retVal = pSolution.findWords(board, words)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
