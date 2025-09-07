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
    def sumZero(self, n: int) -> List[int]:
        retVal = None

        retVal = [0] * n
        for i in range(n//2):
            retVal[i] = (i + 1)
            retVal[n - 1 - i] = -(i + 1)
        if n % 2 == 1:
            retVal[n//2] = 0

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [5, 3, 1]:
            # /* Example
            #  *  Input: n = 5
            #  *  Output: [-7,-1,1,3,4]
            #  *
            #  *  Input: n = 3
            #  *  Output: [-1,0,1]
            #  *
            #  *  Input: n = 1
            #  *  Output: [0]
            #  */
            logging.info("Input:  n = %s",  n)

            retVal = pSolution.sumZero(n)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
