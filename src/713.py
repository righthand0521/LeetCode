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
    def numSubarrayProductLessThanK(self, nums: List[int], k: int) -> int:
        retVal = 0

        # /* the product of nums could not be strictly less than 1
        #  *  1 <= nums.length <= 3 * 10^4
        #  *  1 <= nums[i] <= 1000
        #  *  0 <= k <= 10^6
        #  */
        if k <= 1:
            return retVal

        # /* Sliding window with Two Pointer
        #  *  +--------------------------------------------+
        #  *  |    0   |      1      |   2   |      3      |
        #  *  +--------------------------------------------+
        #  *  |   10   |      5      |   2   |      6      |
        #  *  +--------------------------------------------+
        #  *  |  right -1-> right -2-> right -4-> right    |
        #  *  |  left  -3-> left                           |
        #  *  +--------------------------------------------+
        #  *  | product = 10                               |
        #  *  | product = 50, product = 100                |
        #  *  | product = 10                               |
        #  *  | product = 60                               |
        #  *  +--------------------------------------------+
        #  */
        numsSize = len(nums)
        product = 1
        right = 0
        left = 0
        for right in range(numsSize):
            product *= nums[right]
            while product >= k:
                product /= nums[left]
                left += 1
            retVal += (right - left + 1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[10, 5, 2, 6], [1, 2, 3], [1, 1, 1]], [100, 0, 1]):
            # /* Example
            #  *  Input: nums = [10,5,2,6], k = 100
            #  *  Output: 8
            #  *
            #  *  Input: nums = [1,2,3], k = 0
            #  *  Output: 0
            #  *
            #  *  Input: nums = [1,1,1], k = 1
            #  *  Output: 0
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.numSubarrayProductLessThanK(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
