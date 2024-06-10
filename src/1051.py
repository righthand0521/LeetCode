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
    def heightChecker(self, heights: List[int]) -> int:
        retVal = 0

        expected = sorted(heights)
        for x, y in zip(heights, expected):
            if x != y:
                retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for heights in [[1, 1, 4, 2, 1, 3], [5, 1, 2, 3, 4], [1, 2, 3, 4, 5]]:
            # /* Example
            #  *  Input: heights = [1,1,4,2,1,3]
            #  *  Output: 3
            #  *
            #  *  Input: heights = [5,1,2,3,4]
            #  *  Output: 5
            #  *
            #  *  Input: heights = [1,2,3,4,5]
            #  *  Output: 0
            #  */
            logging.info("Input: heights = %s", heights)

            retVal = pSolution.heightChecker(heights)
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
