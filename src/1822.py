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
    def arraySign(self, nums: List[int]) -> int:
        retVal = 1
        for value in nums:
            if value == 0:
                retVal = 0
                break
            elif value > 1:
                retVal *= 1
            elif value < 1:
                retVal *= (-1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[-1, -2, -3, -4, 3, 2, 1], [1, 5, 0, 2, -3], [-1, 1, -1, 1, -1]]:
            # /* Example
            #  *  Input: nums = [-1,-2,-3,-4,3,2,1]
            #  *  Output: 1
            #  *
            #  *  Input: nums = [1,5,0,2,-3]
            #  *  Output: 0
            #  *
            #  *  Input: nums = [-1,1,-1,1,-1]
            #  *  Output: -1
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.arraySign(nums)
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
