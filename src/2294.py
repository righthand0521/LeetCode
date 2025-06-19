import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop

from random import choice


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
    def partitionArray(self, nums: List[int], k: int) -> int:
        retVal = 1

        nums.sort()

        minValue = nums[0]
        for num in nums:
            if num - minValue > k:
                retVal += 1
                minValue = num

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[3, 6, 1, 2, 5], [1, 2, 3], [2, 2, 4, 5]], [2, 1, 0]):
            # /* Example
            #  *  Input: nums = [3,6,1,2,5], k = 2
            #  *  Output: 2
            #  *
            #  *  Input: nums = [1,2,3], k = 1
            #  *  Output: 2
            #  *
            #  *  Input: nums = [2,2,4,5], k = 0
            #  *  Output: 3
            #  */
            logging.info("Input: nums = %s, coins = %s", nums, k)

            retVal = pSolution.partitionArray(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
