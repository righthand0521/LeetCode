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

if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, val in zip([["WordDictionary", "addWord", "addWord", "addWord", "search", "search", "search", "search"]],
                                [[[], ["bad"], ["dad"], ["mad"], ["pad"], ["bad"], [".ad"], ["b.."]]]):
            # /* Example:
            #  *  Input
            #  *  ["WordDictionary", "addWord", "addWord", "addWord", "search", "search", "search", "search"]
            #  *  [[], ["bad"], ["dad"], ["mad"], ["pad"], ["bad"], [".ad"], ["b.."]]
            #  *  Output
            #  *  [null, null, null, null, false, true, true, true]
            #  */
            logging.info("%s", methods)
            logging.info("%s", val)

            displayStr = []
            for key, value in zip(methods, val):
                if key == "WordDictionary":
                    obj = WordDictionary()
                    displayStr.append(None)
                elif key == "addWord":
                    obj.addWord(value[0])
                    displayStr.append(None)
                elif key == "search":
                    retVal = obj.search(value[0])
                    displayStr.append(retVal)
            logging.info("Output")
            logging.info("%s", displayStr)

            print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass

    sys.exit(0)
