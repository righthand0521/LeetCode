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
    def findLength(self, nums1: List[int], nums2: List[int]) -> int:
        retVal = 0

        #   x 1 2 3 2 1
        # x 0 0 0 0 0 0
        # 3 0 0 0 1 0 0
        # 2 0 0 1 0 2 0
        # 1 0 1 0 0 0 3
        # 4 0 0 0 0 0 0
        # 7 0 0 0 0 0 0
        nums1Size = len(nums1) + 1
        nums2Size = len(nums2) + 1
        dp = [[0 for j in range(nums2Size)] for _ in range(nums1Size)]
        for i in range(1, nums1Size):
            for j in range(1, nums2Size):
                if nums1[i-1] == nums2[j-1]:
                    dp[i][j] = dp[i-1][j-1] + 1
                    retVal = max(retVal, dp[i][j])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums1, nums2 in zip([[1, 2, 3, 2, 1], [0, 0, 0, 0, 0]], [[3, 2, 1, 4, 7], [0, 0, 0, 0, 0]]):
            # /* Example
            #  *  Input: nums1 = [1,2,3,2,1], nums2 = [3,2,1,4,7]
            #  *  Output: 3
            #  *
            #  *  Input: nums1 = [0,0,0,0,0], nums2 = [0,0,0,0,0]
            #  *  Output: 5
            #  */
            logging.info("Input: nums1 = %s, nums2 = %s", nums1, nums2)

            retVal = pSolution.findLength(nums1, nums2)
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
