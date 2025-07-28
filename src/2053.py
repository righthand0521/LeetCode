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
    def kthDistinct(self, arr: List[str], k: int) -> str:
        retVal = ""

        hashTable = defaultdict(int)
        for s in arr:
            hashTable[s] += 1

        for key, value in hashTable.items():
            if value != 1:
                continue

            k -= 1
            if k == 0:
                retVal = key
                break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr, k in zip([["d", "b", "c", "b", "c", "a"], ["aaa", "aa", "a"], ["a", "b", "a"]], [2, 1, 3]):
            # /* Example
            #  *  Input: arr = ["d","b","c","b","c","a"], k = 2
            #  *  Output: "a"
            #  *
            #  *  Input: arr = ["aaa","aa","a"], k = 1
            #  *  Output: "aaa"
            #  *
            #  *  Input: arr = ["a","b","a"], k = 3
            #  *  Output: ""
            #  */
            logging.info("Input: arr = %s, k = %s", arr, k)

            retVal = pSolution.kthDistinct(arr, k)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
