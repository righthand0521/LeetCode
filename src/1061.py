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
        datefmt='%Y/%m/%d %H:%M:%S')


class UnionFind:
    def __init__(self, n) -> None:
        self.uf = list(range(n))

    def find(self, x) -> int:
        retVal = 0

        if self.uf[x] != x:
            self.uf[x] = self.find(self.uf[x])
        retVal = self.uf[x]

        return retVal

    def unite(self, x, y) -> None:
        x = self.find(x)
        y = self.find(y)
        if x == y:
            return

        if x > y:
            x, y = y, x
        self.uf[y] = x


class Solution:
    def smallestEquivalentString(self, s1: str, s2: str, baseStr: str) -> str:
        retVal = ""

        uf = UnionFind(26)  # s1, s2, and baseStr consist of lowercase English letters.
        for a, b in zip(s1, s2):
            uf.unite(ord(a) - ord('a'), ord(b) - ord('a'))
        retVal = ''.join(chr(ord('a') + uf.find(ord(c) - ord('a'))) for c in baseStr)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s1, s2, baseStr in zip(
                ["parker", "hello", "leetcode"],
                ["morris", "world", "programs"],
                ["parser", "hold", "sourcecode"]
        ):
            # /* Example
            #  *  Input: s1 = "parker", s2 = "morris", baseStr = "parser"
            #  *  Output: "makkek"
            #  *
            #  *  Input: s1 = "hello", s2 = "world", baseStr = "hold"
            #  *  Output: "hdld"
            #  *
            #  *  Input: s1 = "leetcode", s2 = "programs", baseStr = "sourcecode"
            #  *  Output: "aauaaaaada"
            #  */
            logging.info("Input: s1 = \"%s\", s2 = \"%s\", baseStr = \"%s\"", s1, s2, baseStr)

            retVal = pSolution.smallestEquivalentString(s1, s2, baseStr)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
