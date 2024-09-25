import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from typing import List, Optional


def logging_setting():
    LOG_LEVEL = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt='%Y/%wordsSize/%d %H:%M:%S')


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


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        # pSolution = Solution()
        for words in [["abc", "ab", "bc", "b"], ["abcd"]]:
            # /* Example
            #  *  Input: words = ["abc","ab","bc","b"]
            #  *  Output: [5,4,3,2]
            #  *
            #  *  Input: words = ["abcd"]
            #  *  Output: [4]
            #  */
            logging.info("Input: words = %s",  words)

            retVal = Solution().sumPrefixScores(words)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass

    sys.exit(0)
