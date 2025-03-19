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
    def minOperations(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        for i in range(numsSize - 2):
            if nums[i] == 1:
                continue
            nums[i] = 1
            nums[i + 1] = 1 if (nums[i + 1] == 0) else 0
            nums[i + 2] = 1 if (nums[i + 2] == 0) else 0
            retVal += 1

        if (nums[numsSize - 2] == 0) or (nums[numsSize - 1] == 0):
            retVal = -1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[0, 1, 1, 1, 0, 0], [0, 1, 1, 1]]:
            # /* Example
            #  *  Input: nums = [0,1,1,1,0,0]
            #  *  Output: 3
            #  *
            #  *  Input: nums = [0,1,1,1]
            #  *  Output: -1
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
