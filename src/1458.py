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
    def maxDotProduct(self, nums1: List[int], nums2: List[int]) -> int:
        retVal = 0

        nums1Size = len(nums1)
        nums2Size = len(nums2)
        dp = [[0] * nums2Size for _ in range(nums1Size)]

        for row in range(nums1Size):
            for col in range(nums2Size):
                product = nums1[row] * nums2[col]

                dp[row][col] = product
                if row > 0:
                    dp[row][col] = max(dp[row][col], dp[row - 1][col])
                if col > 0:
                    dp[row][col] = max(dp[row][col], dp[row][col - 1])
                if row > 0 and col > 0:
                    dp[row][col] = max(dp[row][col], dp[row - 1][col - 1] + product)

        retVal = dp[nums1Size - 1][nums2Size - 1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums1, nums2 in zip([[2, 1, -2, 5], [3, -2], [-1, -1]], [[3, 0, -6], [2, -6, 7], [1, 1]]):
            # /* Example
            #  *  Input: nums1 = [2,1,-2,5], nums2 = [3,0,-6]
            #  *  Output: 18
            #  *
            #  *  Input: nums1 = [3,-2], nums2 = [2,-6,7]
            #  *  Output: 21
            #  *
            #  *  Input: nums1 = [-1,-1], nums2 = [1,1]
            #  *  Output: -1
            #  */
            logging.info("Input: nums1 = %s, nums2 = %s", nums1, nums2)

            retVal = pSolution.maxDotProduct(nums1, nums2)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
