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
    def threeConsecutiveOdds(self, arr: List[int]) -> bool:
        retVal = False

        consecutiveOdds = 0
        for num in arr:
            if num % 2 == 0:
                consecutiveOdds = 0
            else:
                consecutiveOdds += 1
                if consecutiveOdds == 3:
                    retVal = True
                    break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr in [[2, 6, 4, 1], [1, 2, 34, 3, 4, 5, 7, 23, 12]]:
            # /* Example
            #  *  Input: arr = [2,6,4,1]
            #  *  Output: false
            #  *
            #  *  Input: arr = [1,2,34,3,4,5,7,23,12]
            #  *  Output: true
            #  */
            logging.info("Input: arr = %s", arr)

            retVal = pSolution.threeConsecutiveOdds(arr)
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
