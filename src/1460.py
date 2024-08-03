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
    def canBeEqual(self, target: List[int], arr: List[int]) -> bool:
        retVal = True

        hashTable = defaultdict(int)
        for value in target:
            hashTable[value] += 1
        for value in arr:
            hashTable[value] -= 1

        for value in hashTable.values():
            if value != 0:
                retVal = False
                break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for target, arr in zip([[1, 2, 3, 4], [7], [3, 7, 9]], [[2, 4, 1, 3], [7], [3, 7, 11]]):
            # /* Example
            #  *  Input: target = [1,2,3,4], arr = [2,4,1,3]
            #  *  Output: true
            #  *
            #  *  Input: target = [7], arr = [7]
            #  *  Output: true
            #  *
            #  *  Input: target = [3,7,9], arr = [3,7,11]
            #  *  Output: false
            #  */
            logging.info("Input: target = %s, arr = %s", target, arr)

            retVal = pSolution.canBeEqual(target, arr)
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
