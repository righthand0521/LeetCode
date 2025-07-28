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


class Solution:
    def __init__(self) -> None:
        self.ret = None
        self.answer = None

    def isPalindrome(self, s: str, i: int, j: int) -> int:
        retVal = 1

        if i >= j:
            return retVal

        if s[i] == s[j]:
            retVal = self.isPalindrome(s, i + 1, j - 1)
        else:
            retVal = -1

        return retVal

    def dfs(self, s: str, idx: int) -> None:
        sSize = len(s)
        if idx == sSize:
            self.ret.append(self.answer[:])
            return

        for j in range(idx, sSize):
            if self.isPalindrome(s, idx, j) == 1:
                self.answer.append(s[idx:j+1])
                self.dfs(s, j + 1)
                self.answer.pop()

    def partition(self, s: str) -> List[List[str]]:
        retVal = []

        self.ret = list()
        self.answer = list()
        self.dfs(s, 0)
        retVal = self.ret

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["aab", "a"]:
            # /* Example
            #  *  Input: s = "aab"
            #  *  Output: [["a","a","b"],["aa","b"]]
            #  *
            #  *  Input: s = "a"
            #  *  Output: [["a"]]
            #  */
            logging.info("Input: s = '%s'", s)

            retVal = pSolution.partition(s)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
