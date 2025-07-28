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
    def threeSumClosest(self, nums: List[int], target: int) -> int:
        retVal = 0

        nums.sort()

        closest = float('inf')
        numsSize = len(nums)
        for first in range(numsSize-2):
            second = first + 1
            third = numsSize - 1
            while second < third:
                sum = nums[first] + nums[second] + nums[third]
                diff = abs(target-sum)
                if closest > diff:
                    closest = diff
                    retVal = sum

                if sum == target:
                    return retVal
                elif sum < target:
                    second += 1
                elif sum > target:
                    third -= 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, target in [[[-1, 2, 1, -4], 1], [[0, 0, 0], 1], [[4, 0, 5, -5, 3, 3, 0, -4, -5], 2]]:
            # /* Example
            #  *  Input: nums = [-1,2,1,-4], target = 1
            #  *  Output: 2
            #  *
            #  *  Input: nums = [0,0,0], target = 1
            #  *  Output: 0
            #  *
            #  *  Input: nums = [4,0,5,-5,3,3,0,-4,-5], target = -2
            #  *  Output: -2
            #  */
            logging.info("Input: nums = %s, target = %s", nums, target)

            retVal = pSolution.threeSumClosest(nums, target)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
