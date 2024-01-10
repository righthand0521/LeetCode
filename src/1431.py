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
    def kidsWithCandies(self, candies: List[int], extraCandies: int) -> List[bool]:
        retVal = []

        maxCandy = max(candies)
        for candy in candies:
            if candy + extraCandies >= maxCandy:
                retVal.append(True)
            else:
                retVal.append(False)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for candies, extraCandies in zip([[2, 3, 5, 1, 3], [4, 2, 1, 1, 2], [12, 1, 12]], [3, 1, 10]):
            # /* Example
            #  *  Input: candies = [2,3,5,1,3], extraCandies = 3
            #  *  Output: [true,true,true,false,true]
            #  *
            #  *  Input: candies = [4,2,1,1,2], extraCandies = 1
            #  *  Output: [true,false,false,false,false]
            #  *
            #  *  Input: candies = [12,1,12], extraCandies = 10
            #  *  Output: [true,false,true]
            #  */
            logging.info("Input: candies = %s, extraCandies = %s",
                         candies, extraCandies)

            retVal = pSolution.kidsWithCandies(candies, extraCandies)
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
