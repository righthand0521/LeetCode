import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from copy import deepcopy
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
        self.MODULO = 10 ** 9 + 7
        self.letterSize = 26    # s consists only of lowercase English letters.

    def lengthAfterTransformations(self, s: str, t: int) -> int:
        retVal = 0

        hashTable = [0] * self.letterSize
        for ch in s:
            hashTable[ord(ch) - ord("a")] += 1

        for round in range(t):
            next = [0] * self.letterSize
            next[0] = hashTable[self.letterSize - 1]
            next[1] = (hashTable[self.letterSize - 1] + hashTable[0]) % self.MODULO
            for i in range(2, self.letterSize):
                next[i] = hashTable[i - 1]
            hashTable = next
        retVal = sum(hashTable) % self.MODULO

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, t in zip(["abcyy", "azbk"], [2, 1]):
            # /* Example
            #  *  Input: s = "abcyy", t = 2
            #  *  Output: 7
            #  *
            #  *  Input: s = "azbk", t = 1
            #  *  Output: 5
            #  */
            logging.info("Input: senate = \"%s\", t = %s", s, t)

            retVal = pSolution.lengthAfterTransformations(s, t)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
