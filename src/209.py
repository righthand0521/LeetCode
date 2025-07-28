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
    def minSubArrayLen(self, target: int, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        retVal = numsSize + 1
        sum = 0
        head = 0
        for tail in range(numsSize):
            sum += nums[tail]
            while sum >= target:
                retVal = min(retVal, tail - head + 1)
                sum -= nums[head]
                head += 1

        if retVal == numsSize + 1:
            retVal = 0

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for target, nums in zip([7, 4, 11], [[2, 3, 1, 2, 4, 3], [1, 4, 4], [1, 1, 1, 1, 1, 1, 1, 1]]):
            # /* Example
            #  *  Input: target = 7, nums = [2,3,1,2,4,3]
            #  *  Output: 2
            #  *
            #  *  Input: target = 4, nums = [1,4,4]
            #  *  Output: 1
            #  *
            #  *  Input: target = 11, nums = [1,1,1,1,1,1,1,1]
            #  *  Output: 0
            #  */
            logging.info("Input: target = %s, nums = %s", target, nums)

            retVal = pSolution.minSubArrayLen(target, nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
