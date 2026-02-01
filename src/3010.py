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
    def minimumCost(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        min1 = nums[1] if nums[1] < nums[2] else nums[2]
        min2 = nums[2] if nums[1] < nums[2] else nums[1]
        for i in range(3, numsSize):
            if nums[i] <= min1:
                min2 = min1
                min1 = nums[i]
            elif nums[i] < min2:
                min2 = nums[i]
        retVal = nums[0] + min1 + min2

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, 2, 3, 12], [5, 4, 3], [10, 3, 1, 1]]:
            # /* Example
            #  *  Input: nums = [1,2,3,12]
            #  *  Output: 6
            #  *
            #  *  Input: nums = [5,4,3]
            #  *  Output: 12
            #  *
            #  *  Input: nums = [10,3,1,1]
            #  *  Output: 12
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.minimumCost(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
