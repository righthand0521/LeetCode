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
    def __init__(self):
        self.method = 1

        if self.method == 1:
            print("BINARY_SEARCH")
        elif self.method == 2:
            print("DYNAMIC_PROGRAMMING")
        print()

    def lengthOfLIS(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        if numsSize == 0:
            return retVal

        if self.method == 1:
            greedy = [0] * (numsSize + 1)
            idx = 1
            greedy[idx] = nums[0]

            for i in range(1, numsSize):
                if nums[i] > greedy[idx]:
                    idx += 1
                    greedy[idx] = nums[i]
                    continue

                left = 1
                right = idx
                position = 0
                while left < right:
                    middle = left + (right - left) // 2
                    if greedy[middle] < nums[i]:
                        position = middle
                        left = middle + 1
                    else:
                        right = middle
                greedy[position + 1] = nums[i]

            retVal = idx
        elif self.method == 2:
            dp = [0] * numsSize
            for i in range(numsSize):
                dp[i] = 1
                for j in range(i):
                    if nums[j] < nums[i]:
                        dp[i] = max(dp[i], dp[j] + 1)
            retVal = max(dp)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[10, 9, 2, 5, 3, 7, 101, 18], [0, 1, 0, 3, 2, 3], [7, 7, 7, 7, 7, 7, 7]]:
            # /* Example
            #  *  Input: nums = [10,9,2,5,3,7,101,18]
            #  *  Output: 4
            #  *
            #  *  Input: nums = [0,1,0,3,2,3]
            #  *  Output: 4
            #  *
            #  *  Input: nums = [7,7,7,7,7,7,7]
            #  *  Output: 1
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.lengthOfLIS(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
