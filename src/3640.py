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
    def maxSumTrionic(self, nums: List[int]) -> int:
        retVal = float("-inf")

        numsSize = len(nums)

        i = 0
        while i < numsSize:
            j = i + 1
            res = 0

            # first segment: increasing segment
            while (j < numsSize) and (nums[j - 1] < nums[j]):
                j += 1
            p = j - 1
            if p == i:
                i += 1
                continue

            # second segment: decreasing segment
            res += (nums[p] + nums[p - 1])
            while (j < numsSize) and (nums[j - 1] > nums[j]):
                res += nums[j]
                j += 1
            q = j - 1
            if (q == p) or (q == numsSize - 1) or (j < numsSize and nums[j] <= nums[q]):
                i = q
                continue

            # third segment: increasing segment
            res += nums[q + 1]

            # find the maximum sum of the third segment
            maxSum = 0
            currrentSum = 0
            k = q + 2
            while (k < numsSize) and (nums[k] > nums[k - 1]):
                currrentSum += nums[k]
                maxSum = max(maxSum, currrentSum)
                k += 1
            res += maxSum

            # find the maximum sum of the first segment
            maxSum = 0
            currrentSum = 0
            for k in range(p - 2, i - 1, -1):
                currrentSum += nums[k]
                maxSum = max(maxSum, currrentSum)
            res += maxSum

            retVal = max(retVal, res)
            i = q

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[0, -2, -1, -3, 0, 2, -1], [1, 4, 2, 7]]:
            # /* Example
            #  *  Input: nums = [0,-2,-1,-3,0,2,-1]
            #  *  Output: -4
            #  *
            #  *  Input: nums = [1,4,2,7]
            #  *  Output: 14
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.maxSumTrionic(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
