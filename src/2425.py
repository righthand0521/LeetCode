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
    def xorAllNums(self, nums1: List[int], nums2: List[int]) -> int:
        retVal = 0

        nums1Size = len(nums1)
        nums2Size = len(nums2)

        xor1 = 0
        if nums2Size % 2:
            for num in nums1:
                xor1 ^= num

        xor2 = 0
        if nums1Size % 2:
            for num in nums2:
                xor2 ^= num

        retVal = xor1 ^ xor2

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums1, nums2 in zip([[2, 1, 3], [1, 2]], [[10, 2, 5, 0], [3, 4]]):
            # /* Example
            #  *  Input: nums1 = [2,1,3], nums2 = [10,2,5,0]
            #  *  Output: 13
            #  *
            #  *  Input: nums1 = [1,2], nums2 = [3,4]
            #  *  Output: 0
            #  */
            logging.info("Input: nums1 = %s, nums2 = %s", nums1, nums2)

            retVal = pSolution.xorAllNums(nums1, nums2)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass

    sys.exit(0)
