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
    def checkIfExist(self, arr: List[int]) -> bool:
        retVal = False

        hashTable = defaultdict(int)
        for value in arr:
            hashTable[value] += 1

        for value in arr:
            if (value == 0) and (hashTable[value] > 1):
                retVal = True
                break
            elif (value != 0) and ((2*value) in hashTable):
                retVal = True
                break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print("")

        pSolution = Solution()
        for arr in [[10, 2, 5, 3], [3, 1, 7, 11], [-2, 0, 10, -19, 4, 6, -8], [0, 0], [-10, 12, -20, -8, 15]]:
            # /* Example
            #  *  Input: arr = [10,2,5,3]
            #  *  Output: true
            #  *
            #  *  Input: arr = [3,1,7,11]
            #  *  Output: false
            #  *
            #  *  Input: arr = [-2, 0, 10, -19, 4, 6, -8]
            #  *  Output: false
            #  *
            #  *  Input: arr = [0, 0]
            #  *  Output: true
            #  *
            #  *  Input: arr = [-10, 12, -20, -8, 15]
            #  *  Output: true
            #  */
            logging.info("Input: arr = %s", arr)

            retVal = pSolution.checkIfExist(arr)
            logging.info("Output: %s", retVal)

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
