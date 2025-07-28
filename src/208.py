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


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, val in zip([["Trie", "insert", "search", "search", "startsWith", "insert", "search"]],
                                [[[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]]):
            # /* Example
            #  *  Input
            #  *  ["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
            #  *  [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
            #  *  Output
            #  *  [null, null, true, false, true, null, true]
            #  */
            logging.info("%s", methods)
            logging.info("%s", val)

            displayStr = []
            for key, value in zip(methods, val):
                if key == "Trie":
                    obj = Trie()
                    displayStr.append(None)
                elif key == "insert":
                    obj.insert(value[0])
                    displayStr.append(None)
                elif key == "search":
                    retVal = obj.search(value[0])
                    displayStr.append(retVal)
                elif key == "startsWith":
                    retVal = obj.startsWith(value[0])
                    displayStr.append(retVal)
            logging.info("Output")
            logging.info("%s", displayStr)

            print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
