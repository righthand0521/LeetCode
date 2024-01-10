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
    def kSmallestPairs(self, nums1: List[int], nums2: List[int], k: int) -> List[List[int]]:
        retVal = []

        nums1Size = len(nums1)
        nums2Size = len(nums2)

        visited = set()

        minHeap = [(nums1[0] + nums2[0], (0, 0))]
        visited.add((0, 0))
        count = 0
        while k > 0 and minHeap:
            val, (i, j) = heappop(minHeap)
            retVal.append([nums1[i], nums2[j]])

            if i + 1 < nums1Size and (i + 1, j) not in visited:
                heappush(minHeap, (nums1[i + 1] + nums2[j], (i + 1, j)))
                visited.add((i + 1, j))

            if j + 1 < nums2Size and (i, j + 1) not in visited:
                heappush(minHeap, (nums1[i] + nums2[j + 1], (i, j + 1)))
                visited.add((i, j + 1))

            k = k - 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums1, nums2, k in zip([[1, 7, 11], [1, 1, 2], [1, 2]], [[2, 4, 6], [1, 2, 3], [3]], [3, 2, 3]):
            # /* Example
            #  *  Input: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
            #  *  Output: [[1,2],[1,4],[1,6]]
            #  *
            #  *  Input: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
            #  *  Output: [[1,1],[1,1]]
            #  *
            #  *  Input: nums1 = [1,2], nums2 = [3], k = 3
            #  *  Output: [[1,3],[2,3]]
            #  */
            logging.info("Input: nums1 = %s, nums2 = %s, k = %s",
                         nums1, nums2, k)

            retVal = pSolution.kSmallestPairs(nums1, nums2, k)
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
