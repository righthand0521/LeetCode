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
    def findLucky(self, arr: List[int]) -> int:
        retVal = -1

        hashTable = defaultdict(int)
        for value in arr:
            hashTable[value] += 1
        for key, count in hashTable.items():
            if key == count:
                retVal = max(retVal, key)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr in [[2, 2, 3, 4], [1, 2, 2, 3, 3, 3], [2, 2, 2, 3, 3]]:
            # /* Example
            #  *  Input: arr = [2,2,3,4]
            #  *  Output: 2
            #  *
            #  *  Input: arr = [1,2,2,3,3,3]
            #  *  Output: 3
            #  *
            #  *  Input: arr = [2,2,2,3,3]
            #  *  Output: -1
            #  */
            logging.info("Input: arr = %s", arr)

            retVal = pSolution.findLucky(arr)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
