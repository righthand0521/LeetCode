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
    def merge(self, nums1: List[int], m: int, nums2: List[int], n: int) -> None:
        """
        Do not return anything, modify nums1 in-place instead.
        """
        nums1Size = len(nums1)
        if m+n > nums1Size:
            return

        idx = nums1Size - 1
        idx1 = m - 1
        idx2 = n - 1
        while ((idx1 >= 0) and (idx2 >= 0)):
            if nums1[idx1] > nums2[idx2]:
                nums1[idx] = nums1[idx1]
                idx -= 1
                idx1 -= 1
            else:
                nums1[idx] = nums2[idx2]
                idx -= 1
                idx2 -= 1

        while (idx1 >= 0):
            nums1[idx] = nums1[idx1]
            idx -= 1
            idx1 -= 1

        while (idx2 >= 0):
            nums1[idx] = nums2[idx2]
            idx -= 1
            idx2 -= 1


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums1, m, nums2, n in zip([[1, 2, 3, 0, 0, 0], [1], [0]], [3, 1, 0], [[2, 5, 6], [], [1]], [3, 0, 1]):
            # /* Example
            #  *  Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
            #  *  Output: [1,2,2,3,5,6]
            #  *
            #  *  Input: nums1 = [1], m = 1, nums2 = [], n = 0
            #  *  Output: [1]
            #  *
            #  *  Input: nums1 = [0], m = 0, nums2 = [1], n = 1
            #  *  Output: [1]
            #  */
            logging.info(
                "Input: nums1 = %s, m = %s, nums2 = %s, n = %s", nums1, m, nums2, n)

            pSolution.merge(nums1, m, nums2, n)
            logging.info("Output: %s", nums1)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
