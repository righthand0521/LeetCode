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
    def kthSmallestProduct(self, nums1: List[int], nums2: List[int], k: int) -> int:
        retVal = 0

        nums1Size = len(nums1)
        nums2Size = len(nums2)

        pos1 = 0
        while (pos1 < nums1Size) and (nums1[pos1] < 0):
            pos1 += 1
        pos2 = 0
        while (pos2 < nums2Size) and (nums2[pos2] < 0):
            pos2 += 1

        left = int(-1e10)
        right = int(1e10)
        while left <= right:
            middle = (left + right) // 2
            count = 0

            i1 = 0
            i2 = pos2 - 1
            while (i1 < pos1) and (i2 >= 0):
                if nums1[i1] * nums2[i2] > middle:
                    i1 += 1
                else:
                    count += (pos1 - i1)
                    i2 -= 1

            i1 = pos1
            i2 = nums2Size - 1
            while (i1 < nums1Size) and (i2 >= pos2):
                if nums1[i1] * nums2[i2] > middle:
                    i2 -= 1
                else:
                    count += (i2 - pos2 + 1)
                    i1 += 1

            i1 = 0
            i2 = pos2
            while (i1 < pos1) and (i2 < nums2Size):
                if nums1[i1] * nums2[i2] > middle:
                    i2 += 1
                else:
                    count += (nums2Size - i2)
                    i1 += 1

            i1 = pos1
            i2 = 0
            while (i1 < nums1Size) and (i2 < pos2):
                if nums1[i1] * nums2[i2] > middle:
                    i1 += 1
                else:
                    count += (nums1Size - i1)
                    i2 += 1

            if count < k:
                left = middle + 1
            else:
                right = middle - 1

        retVal = left

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums1, nums2, k in zip(
            [[2, 5], [-4, -2, 0, 3], [-2, -1, 0, 1, 2]],
            [[3, 4], [2, 4], [-3, -1, 2, 4, 5]],
            [2, 6, 3]
        ):
            # /* Example
            #  *  Input: nums1 = [2,5], nums2 = [3,4], k = 2
            #  *  Output: 8
            #  *
            #  *  Input: nums1 = [-4,-2,0,3], nums2 = [2,4], k = 6
            #  *  Output: 0
            #  *
            #  *  Input: nums1 = [-2,-1,0,1,2], nums2 = [-3,-1,2,4,5], k = 3
            #  *  Output: -6
            #  */
            logging.info("Input: nums1 = %s, nums2 = %s, k = %s", nums1, nums2, k)

            retVal = pSolution.kthSmallestProduct(nums1, nums2, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
