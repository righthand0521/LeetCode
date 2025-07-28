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
    def getCommon(self, nums1: List[int], nums2: List[int]) -> int:
        retVal = -1

        num1Size = len(nums1)
        num2Size = len(nums2)

        nums1Idx = 0
        nums2Idx = 0
        while (nums1Idx < num1Size) and (nums2Idx < num2Size):
            if nums1[nums1Idx] == nums2[nums2Idx]:
                retVal = nums1[nums1Idx]
                break
            elif nums1[nums1Idx] > nums2[nums2Idx]:
                nums2Idx += 1
            elif nums1[nums1Idx] < nums2[nums2Idx]:
                nums1Idx += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums1, nums2 in zip([[1, 2, 3], [1, 2, 3, 6]], [[2, 4], [2, 3, 4, 5]]):
            # /* Example
            #  *  Input: nums1 = [1,2,3], nums2 = [2,4]
            #  *  Output: 2
            #  *
            #  *  Input: nums1 = [1,2,3,6], nums2 = [2,3,4,5]
            #  *  Output: 2
            #  */
            logging.info("Input: nums1 = %s, nums2 = %s", nums1, nums2)

            retVal = pSolution.getCommon(nums1, nums2)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
