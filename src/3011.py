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
    def canSortArray(self, nums: List[int]) -> bool:
        retVal = True

        lastCnt = 0
        lastGroupMax = 0
        curGroupMax = 0
        for num in nums:
            curCnt = num.bit_count()
            if curCnt == lastCnt:
                curGroupMax = max(curGroupMax, num)
            else:
                lastCnt = curCnt
                lastGroupMax = curGroupMax
                curGroupMax = num

            if num < lastGroupMax:
                retVal = False
                break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[8, 4, 2, 30, 15], [1, 2, 3, 4, 5], [3, 16, 8, 4, 2]]:
            # /* Example
            #  *  Input: nums = [8,4,2,30,15]
            #  *  Output: true
            #  *
            #  *  Input: nums = [1,2,3,4,5]
            #  *  Output: true
            #  *
            #  *  Input: nums = [3,16,8,4,2]
            #  *  Output: false
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.canSortArray(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
