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


class Solution:
    # https://leetcode.com/problems/scramble-string/solutions/1570555/python-DFS-+-MEMO-and-elegant-negative-index/
    @cache  # Time Limit Exceeded
    def isScramble(self, s1: str, s2: str) -> bool:
        retVal = False

        if s1 == s2:
            retVal = True
            return retVal

        if Counter(s1) != Counter(s2):
            return retVal

        n = len(s1)
        for i in range(1, n):
            if self.isScramble(s1[:i], s2[:i]) and self.isScramble(s1[i:], s2[i:]):
                retVal = True
                return retVal
            if self.isScramble(s1[:i], s2[-i:]) and self.isScramble(s1[i:], s2[:-i]):
                retVal = True
                return retVal

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s1, s2 in zip(["great", "abcde", "a"], ["rgeat", "caebd", "a"]):
            # /* Example
            #  *  Input: s1 = "great", s2 = "rgeat"
            #  *  Output: true
            #  *
            #  *  Input: s1 = "abcde", s2 = "caebd"
            #  *  Output: false
            #  *
            #  *  Input: s1 = "a", s2 = "a"
            #  *  Output: true
            #  */
            logging.info("Input: s1 = \"%s\", s2 = \"%s\"", s1, s2)

            retVal = pSolution.isScramble(s1, s2)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
