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
    def maxCoins(self, piles: List[int]) -> int:
        retVal = 0

        pilesSize = len(piles)
        piles.sort()

        left = 0
        right = pilesSize - 1
        while left < right:
            right -= 1
            retVal += piles[right]
            right -= 1
            left += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for piles in [[2, 4, 1, 2, 7, 8], [2, 4, 5], [9, 8, 7, 6, 5, 1, 2, 3, 4]]:
            # /* Example
            #  *  Input: piles = [2,4,1,2,7,8]
            #  *  Output: 9
            #  *
            #  *  Input: piles = [2,4,5]
            #  *  Output: 4
            #  *
            #  *  Input: piles = [9,8,7,6,5,1,2,3,4]
            #  *  Output: 18
            #  */
            logging.info("Input: piles = %s", piles)

            retVal = pSolution.maxCoins(piles)
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
