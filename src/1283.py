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
    def smallestDivisor(self, nums: List[int], threshold: int) -> int:
        retVal = 0

        left = 1
        right = max(nums)
        while left < right:
            middle = left + (right - left) // 2

            sum = 0
            for num in nums:
                sum += ((num + middle - 1) // middle)

            if sum > threshold:
                left = middle + 1
            else:
                right = middle
        retVal = left

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, threshold in zip([[1, 2, 5, 9], [44, 22, 33, 11, 1]], [6, 5]):
            # /* Example
            #  *  Input: nums = [1,2,5,9], threshold = 6
            #  *  Output: 5
            #  *
            #  *  Input: nums = [44,22,33,11,1], threshold = 5
            #  *  Output: 44
            #  */
            logging.info("Input: nums = %s, threshold = %s", nums, threshold)

            retVal = pSolution.smallestDivisor(nums, threshold)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
