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
    def maxSubarrayLength(self, nums: List[int], k: int) -> int:
        retVal = 0

        frequency = defaultdict(int)
        start = -1
        for end, value in enumerate(nums):
            frequency[value] += 1
            while frequency[value] > k:
                start += 1
                frequency[nums[start]] -= 1
            retVal = max(retVal, end - start)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[1, 2, 3, 1, 2, 3, 1, 2], [1, 2, 1, 2, 1, 2, 1, 2], [5, 5, 5, 5, 5, 5, 5], [1, 4, 4, 3]],
                           [2, 1, 4, 1]):
            # /* Example
            #  *  Input: nums = [1,2,3,1,2,3,1,2], k = 2
            #  *  Output: 6
            #  *
            #  *  Input: nums = [1,2,1,2,1,2,1,2], k = 1
            #  *  Output: 2
            #  *
            #  *  Input: nums = [5,5,5,5,5,5,5], k = 4
            #  *  Output: 4
            #  *
            #  *  Input: nums = [1,4,4,3], k = 1
            #  *  Output: 2
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.maxSubarrayLength(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
