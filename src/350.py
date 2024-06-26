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
    def intersect(self, nums1: List[int], nums2: List[int]) -> List[int]:
        retVal = []

        hashTable = defaultdict(int)
        for num in nums1:
            hashTable[num] += 1

        for num in nums2:
            if hashTable[num] != 0:
                retVal.append(num)
                hashTable[num] -= 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums1, nums2 in zip([[1, 2, 2, 1], [4, 9, 5]], [[2, 2], [9, 4, 9, 8, 4]]):
            # /* Example
            #  *  Input: nums1 = [1,2,2,1], nums2 = [2,2]
            #  *  Output: [2,2]
            #  *
            #  *  Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
            #  *  Output: [4,9]
            #  */
            logging.info("Input: nums1 = %s, nums2 = %s", nums1, nums2)

            retVal = pSolution.intersect(nums1, nums2)
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
