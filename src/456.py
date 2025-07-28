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
    def find132pattern(self, nums: List[int]) -> bool:
        retVal = False

        numsSize = len(nums)
        if numsSize < 3:
            return retVal

        minStack = [nums[0]]
        for i in range(1, numsSize):
            minStack.append(min(minStack[i-1], nums[i]))

        middleStack = []
        for i in range(numsSize - 1, -1, -1):
            if nums[i] <= minStack[i]:
                continue

            while (middleStack) and (middleStack[-1] <= minStack[i]):
                middleStack.pop()

            if (middleStack) and (middleStack[-1] < nums[i]):
                retVal = True
                break

            middleStack.append(nums[i])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, 2, 3, 4], [3, 1, 4, 2], [-1, 3, 2, 0], [1, 2, 3, 4, 0], [3, 5, 0, 3, 4], [2, 3, 1, 2]]:
            # /* Example
            #  *  Input: nums = [1,2,3,4]
            #  *  Output: false
            #  *
            #  *  Input: nums = [3,1,4,2]
            #  *  Output: true
            #  *
            #  *  Input: nums = [-1,3,2,0]
            #  *  Output: true
            #  *
            #  *  Input: nums = [1,2,3,4,0]
            #  *  Output: false
            #  *
            #  *  Input: nums = [3,5,0,3,4]
            #  *  Output: true
            #  *
            #  *  Input: nums = [2,3,1,2]
            #  *  Output: false
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.find132pattern(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
