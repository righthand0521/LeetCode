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
    def minOperations(self, nums: List[int]) -> int:
        retVal = 0

        monotonicStack = []
        for num in nums:
            while (monotonicStack) and (monotonicStack[-1] > num):
                monotonicStack.pop()
            if num == 0:
                continue

            if (not monotonicStack) or (monotonicStack[-1] < num):
                retVal += 1
                monotonicStack.append(num)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[0, 2], [3, 1, 2, 1], [1, 2, 1, 2, 1, 2]]:
            # /* Example
            #  *  Input: nums = [0,2]
            #  *  Output: 1
            #  *
            #  *  Input: nums = [3,1,2,1]
            #  *  Output: 3
            #  *
            #  *  Input: nums = [1,2,1,2,1,2]
            #  *  Output: 4
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.minOperations(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
