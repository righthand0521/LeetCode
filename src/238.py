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
    def productExceptSelf(self, nums: List[int]) -> List[int]:
        retVal = []

        numsSize = len(nums)

        #  1  2  3  4
        # x1 24 12  4 => 1 x 24 = 24
        #  1 x1 12  4 => 1 x 12 = 12
        #  1  2 x1  4 => 2 x  4 =  8
        #  1  2  6 x1 => 6 x  1 =  6
        retVal = [1] * numsSize
        for i in range(1, numsSize):
            retVal[i] = retVal[i - 1] * nums[i - 1]
        tmp = 1
        for i in range(numsSize - 2, -1, -1):
            tmp *= nums[i + 1]
            retVal[i] *= tmp

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, 2, 3, 4], [-1, 1, 0, -3, 3]]:
            # /* Example
            #  *  Input: nums = [1,2,3,4]
            #  *  Output: [24,12,8,6]
            #  *
            #  *  Input: nums = [-1,1,0,-3,3]
            #  *  Output: [0,0,9,0,0]
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.productExceptSelf(nums)
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
