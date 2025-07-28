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
    def getMaximumXor(self, nums: List[int], maximumBit: int) -> List[int]:
        retVal = []

        numsSize = len(nums)

        xorProduct = 0
        for i in range(numsSize):
            xorProduct = xorProduct ^ nums[i]

        mask = (1 << maximumBit) - 1
        for i in range(numsSize):
            retVal.append(xorProduct ^ mask)
            # remove last element
            xorProduct = xorProduct ^ nums[numsSize - 1 - i]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, maximumBit in zip([[0, 1, 1, 3], [2, 3, 4, 7], [0, 1, 2, 2, 5, 7]], [2, 3, 3]):
            # /* Example
            #  *  Input: nums = [0,1,1,3], maximumBit = 2
            #  *  Output: [0,3,2,3]
            #  *
            #  *  Input: nums = [2,3,4,7], maximumBit = 3
            #  *  Output: [5,2,6,5]
            #  *
            #  *  Input: nums = [0,1,2,2,5,7], maximumBit = 3
            #  *  Output: [4,3,6,4,6,7]
            #  */
            logging.info("Input: nums = %s, maximumBit = %s", nums, maximumBit)

            retVal = pSolution.getMaximumXor(nums, maximumBit)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
