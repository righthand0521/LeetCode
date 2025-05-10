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
    def minSum(self, nums1: List[int], nums2: List[int]) -> int:
        retVal = -1

        sum1 = 0
        zero1 = 0
        for num in nums1:
            sum1 += num
            if num == 0:
                sum1 += 1
                zero1 += 1

        sum2 = 0
        zero2 = 0
        for num in nums2:
            sum2 += num
            if num == 0:
                sum2 += 1
                zero2 += 1

        if (zero1 == 0 and sum2 > sum1) or (zero2 == 0 and sum1 > sum2):
            return retVal
        retVal = max(sum1, sum2)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums1, nums2 in zip([[3, 2, 0, 1, 0], [2, 0, 2, 0]], [[6, 5, 0], [1, 4]]):
            # /* Example
            #  *  Input: nums1 = [3,2,0,1,0], nums2 = [6,5,0]
            #  *  Output: 12
            #  *
            #  *  Input: nums1 = [2,0,2,0], nums2 = [1,4]
            #  *  Output: -1
            #  */
            logging.info("Input: nums1 = %s, nums2 = %s", nums1, nums2)

            retVal = pSolution.minSum(nums1, nums2)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
