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
    def smallestDistancePair(self, nums: List[int], k: int) -> int:
        retVal = 0

        nums.sort()

        numsSize = len(nums)
        left = 0
        right = nums[numsSize - 1] - nums[0]
        while left <= right:
            middle = (left + right) // 2

            index = 0
            i = 0
            for j in range(numsSize):
                while nums[j] - nums[i] > middle:
                    i += 1
                index += (j-i)

            if index >= k:
                right = middle - 1
            else:
                left = middle + 1

        retVal = left

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[1, 3, 1], [1, 1, 1], [1, 6, 1]], [1, 2, 3]):
            # /* Example
            #  *  Input: nums = [1,3,1], k = 1
            #  *  Output: 0
            #  *
            #  *  Input: nums = [1,1,1], k = 2
            #  *  Output: 0
            #  *
            #  *  Input: nums = [1,6,1], k = 3
            #  *  Output: 5
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.smallestDistancePair(nums, k)
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
