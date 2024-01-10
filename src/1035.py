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
    def maxUncrossedLines(self, nums1: List[int], nums2: List[int]) -> int:
        retVal = 0

        nums1Size = len(nums1)
        nums2Size = len(nums2)

        # /* Example: Input: nums1 = [2,5,1,2,5], nums2 = [10,5,2,1,5,2]
        #  *     10 5 2 1 5 2
        #  *    0 0 0 0 0 0 0
        #  *  2 0 0 0 1 1 1 1
        #  *  5 0 0 1 1 1 2 2
        #  *  1 0 0 1 1 2 2 2
        #  *  2 0 0 1 2 2 2 3
        #  *  5 0 0 1 2 2 3 3
        #  */
        dp = [[0] * (nums2Size + 1) for _ in range(nums1Size + 2)]
        for idx1 in range(1, nums1Size + 1):
            for idx2 in range(1, nums2Size + 1, 1):
                if nums1[idx1 - 1] == nums2[idx2 - 1]:
                    dp[idx1][idx2] = dp[idx1 - 1][idx2 - 1] + 1
                else:
                    dp[idx1][idx2] = max(
                        dp[idx1 - 1][idx2], dp[idx1][idx2 - 1])
        retVal = dp[nums1Size][nums2Size]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums1, nums2 in zip([[1, 4, 2], [2, 5, 1, 2, 5], [1, 3, 7, 1, 7, 5]],
                                [[1, 2, 4], [10, 5, 2, 1, 5, 2], [1, 9, 2, 5, 1]]):
            # /* Example
            #  *  Input: nums1 = [1,4,2], nums2 = [1,2,4]
            #  *  Output: 2
            #  *
            #  *  Input: nums1 = [2,5,1,2,5], nums2 = [10,5,2,1,5,2]
            #  *  Output: 3
            #  *
            #  *  Input: nums1 = [1,3,7,1,7,5], nums2 = [1,9,2,5,1]
            #  *  Output: 2
            #  */
            logging.info("Input: nums1 = %s, nums2 = %s", nums1, nums2)

            retVal = pSolution.maxUncrossedLines(nums1, nums2)
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
