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
    def mergeArrays(self, nums1: List[List[int]], nums2: List[List[int]]) -> List[List[int]]:
        retVal = []

        nums1Size = len(nums1)
        nums2Size = len(nums2)

        idx1 = 0
        idx2 = 0
        while (idx1 < nums1Size) and (idx2 < nums2Size):
            if nums1[idx1][0] == nums2[idx2][0]:
                retVal.append([nums1[idx1][0], nums1[idx1][1] + nums2[idx2][1]])
                idx1 += 1
                idx2 += 1
            elif nums1[idx1][0] < nums2[idx2][0]:
                retVal.append([nums1[idx1][0], nums1[idx1][1]])
                idx1 += 1
            elif nums1[idx1][0] > nums2[idx2][0]:
                retVal.append([nums2[idx2][0], nums2[idx2][1]])
                idx2 += 1

        while (idx1 < nums1Size):
            retVal.append([nums1[idx1][0], nums1[idx1][1]])
            idx1 += 1
        while (idx2 < nums2Size):
            retVal.append([nums2[idx2][0], nums2[idx2][1]])
            idx2 += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums1, nums2 in zip([[[1, 2], [2, 3], [4, 5]], [[2, 4], [3, 6], [5, 5]]],
                                [[[1, 4], [3, 2], [4, 1]], [[1, 3], [4, 3]]]):
            # /* Example
            #  *  Input: nums1 = [[1,2],[2,3],[4,5]], nums2 = [[1,4],[3,2],[4,1]]
            #  *  Output: [[1,6],[2,3],[3,2],[4,6]]
            #  *
            #  *  Input: nums1 = [[2,4],[3,6],[5,5]], nums2 = [[1,3],[4,3]]
            #  *  Output: [[1,3],[2,4],[3,6],[4,3],[5,5]]
            #  */
            logging.info("Input: nums1 = %s, nums2 = %s", nums1, nums2)

            retVal = pSolution.mergeArrays(nums1, nums2)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
