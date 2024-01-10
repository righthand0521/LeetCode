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
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        retVal = 0

        numsMerge = sorted(nums1 + nums2)
        numsMergeSize = len(numsMerge)

        if numsMergeSize % 2 == 1:
            retVal = float(numsMerge[numsMergeSize // 2])
        else:
            retVal = float(
                (numsMerge[numsMergeSize // 2 - 1] + numsMerge[numsMergeSize // 2]) / 2)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums1, nums2 in zip([[1, 3], [1, 2], [1], [1]], [[2], [3, 4], [], [2]]):
            # /* Example
            #  *  Input: nums1 = [1,3], nums2 = [2]
            #  *  Output: 2.00000
            #  *
            #  *  Input: nums1 = [1,2], nums2 = [3,4]
            #  *  Output: 2.50000
            #  *
            #  *  Input: nums1 = [1], nums2 = []
            #  *  Output: 1.00000
            #  *
            #  *  Input: nums1 = [1], nums2 = [2]
            #  *  Output: 1.50000
            #  */
            logging.info("Input: nums1 = %s, nums2 = %s", nums1, nums2)

            retVal = pSolution.findMedianSortedArrays(nums1, nums2)
            logging.info("Output: %.5f", retVal)

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
