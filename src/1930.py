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
    def __init__(self) -> None:
        self.lettersSize = 26   # s consists of only lowercase English letters.

    def countPalindromicSubsequence(self, s: str) -> int:
        retVal = 0

        sSize = len(s)

        left = [-1] * self.lettersSize
        right = [-1] * self.lettersSize
        for i in range(sSize):
            idx = ord(s[i]) - ord('a')
            if left[idx] == -1:
                left[idx] = i
            right[idx] = i

        for i in range(self.lettersSize):
            if left[i] == -1:
                continue

            between = set()
            for j in range(left[i] + 1, right[i]):
                between.add(s[j])
            retVal += len(between)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["aabca", "adc", "bbcbaba"]:
            # /* Example
            #  *  Input: s = "aabca"
            #  *  Output: 3
            #  *
            #  *  Input: s = "adc"
            #  *  Output: 0
            #  *
            #  *  Input: s = "bbcbaba"
            #  *  Output: 4
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.countPalindromicSubsequence(s)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
