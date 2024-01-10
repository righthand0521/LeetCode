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
    def maxProductDifference(self, nums: List[int]) -> int:
        retVal = 0

        nums.sort()
        retVal = (nums[-1] * nums[-2]) - (nums[0] * nums[1])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[5, 6, 2, 7, 4], [4, 2, 5, 9, 7, 4, 8]]:
            # /* Example
            #  *  Input: nums = [5,6,2,7,4]
            #  *  Output: 34
            #  *
            #  *  Input: nums = [4,2,5,9,7,4,8]
            #  *  Output: 64
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.maxProductDifference(nums)
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
