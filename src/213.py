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
    def robHouse(self, nums: List[int], start: int, end: int) -> int:
        retVal = 0

        first = nums[start]
        second = max(nums[start], nums[start + 1])
        for i in range(start + 2, end):
            first, second = second, max(first + nums[i], second)
        retVal = second

        return retVal

    def rob(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        if numsSize == 1:
            retVal = nums[0]
        elif numsSize == 2:
            retVal = max(nums[0], nums[1])
        else:
            robStartFirst = self.robHouse(nums, 0, numsSize - 1)
            robStartSecond = self.robHouse(nums, 1, numsSize)
            retVal = max(robStartFirst, robStartSecond)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[2, 3, 2], [1, 2, 3, 1], [1, 2, 3]]:
            # /* Example
            #  *  Input: nums = [2,3,2]
            #  *  Output: 3
            #  *
            #  *  Input: nums = [1,2,3,1]
            #  *  Output: 4
            #  *
            #  *  Input: nums = [1,2,3]
            #  *  Output: 3
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.rob(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
