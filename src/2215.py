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
    def findDifference(self, nums1: List[int], nums2: List[int]) -> List[List[int]]:
        retVal = [[], []]

        hashTable1 = set(nums1)
        hashTable2 = set(nums2)
        retVal = [list(hashTable1-hashTable2), list(hashTable2-hashTable1)]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums1, nums2 in zip([[1, 2, 3], [1, 2, 3, 3]], [[2, 4, 6], [1, 1, 2, 2]]):
            # /* Example
            #  *  Input: nums1 = [1,2,3], nums2 = [2,4,6]
            #  *  Output: [[1,3],[4,6]]
            #  *
            #  *  Input: nums1 = [1,2,3,3], nums2 = [1,1,2,2]
            #  *  Output: [[3],[]]
            #  */
            logging.info("Input: nums = %s, nums2 = %s", nums1, nums2)

            retVal = pSolution.findDifference(nums1, nums2)
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
