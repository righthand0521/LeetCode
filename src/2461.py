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
    def maximumSubarraySum(self, nums: List[int], k: int) -> int:
        retVal = 0

        numsSize = len(nums)

        numToIndex = {}
        currentSum = 0
        begin = 0
        end = 0
        while end < numsSize:
            currNum = nums[end]
            lastOccurrence = numToIndex.get(currNum, -1)

            # if current window already has number or if window is too big, adjust window
            while (begin <= lastOccurrence) or (end - begin + 1 > k):
                currentSum -= nums[begin]
                begin += 1

            numToIndex[currNum] = end
            currentSum += nums[end]
            if end - begin + 1 == k:
                retVal = max(retVal, currentSum)

            end += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[1, 5, 4, 2, 9, 9, 9], [4, 4, 4]], [3, 3]):
            # /* Example
            #  *  Input: nums = [1,5,4,2,9,9,9], k = 3
            #  *  Output: 15
            #  *
            #  *  Input: nums = [4,4,4], k = 3
            #  *  Output: 0
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.maximumSubarraySum(nums, k)
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
