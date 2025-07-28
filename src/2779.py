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
    def maximumBeauty(self, nums: List[int], k: int) -> int:
        retVal = 0

        numsSize = len(nums)
        if numsSize == 1:  # If there's only one element, the maximum beauty is 1
            retVal = 1
            return retVal

        maxValue = max(nums)
        count = [0] * (maxValue + 1)
        for num in nums:
            count[max(num - k, 0)] += 1  # Increment at the start of the range
            if num + k + 1 <= maxValue:
                count[num + k + 1] -= 1  # Decrement after the range

        # Calculate the prefix sum and find the maximum beauty
        currentSum = 0
        for value in count:
            currentSum += value
            retVal = max(retVal, currentSum)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[4, 6, 1, 2], [1, 1, 1, 1]], [2, 10]):
            # /* Example
            #  *  Input: nums = [4,6,1,2], k = 2
            #  *  Output: 3
            #  *
            #  *  Input: nums = [1,1,1,1], k = 10
            #  *  Output: 4
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.maximumBeauty(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
