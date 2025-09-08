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
    def getNoZeroIntegers(self, n: int) -> List[int]:
        retVal = [0] * 2

        for a in range(1, n):
            b = n - a
            if ('0' not in str(a)) and ('0' not in str(b)):
                retVal[0] = a
                retVal[1] = b
                break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [2, 11]:
            # /* Example
            #  *  Input: n = 2
            #  *  Output: [1,1]
            #  *
            #  *  Input: n = 11
            #  *  Output: [2,9]
            #  */
            logging.info("Input:  n = %s",  n)

            retVal = pSolution.getNoZeroIntegers(n)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
