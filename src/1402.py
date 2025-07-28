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
    def maxSatisfaction(self, satisfaction: List[int]) -> int:
        retVal = 0

        satisfaction.sort(reverse=True)

        sum = 0
        for i in satisfaction:
            sum += i
            if sum >= 0:
                retVal += sum

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for satisfaction in [[-1, -8, 0, 5, -9], [4, 3, 2], [-1, -4, -5]]:
            # /* Example
            #  *  Input: satisfaction = [-1,-8,0,5,-9]
            #  *  Output: 14
            #  *
            #  *  Input: satisfaction = [4,3,2]
            #  *  Output: 20
            #  *
            #  *  Input: satisfaction = [-1,-4,-5]
            #  *  Output: 0
            #  */
            logging.info("Input: satisfaction = %s", satisfaction)

            retVal = pSolution.maxSatisfaction(satisfaction)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
