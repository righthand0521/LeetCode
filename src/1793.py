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
    def maximumScore(self, nums: List[int], k: int) -> int:
        retVal = 0

        numsSize = len(nums)

        retVal = nums[k]
        minValue = nums[k]
        left = k
        right = k
        while (left > 0) or (right < numsSize-1):
            # 1 <= nums[i] <= 2 * 10^4, 0 <= k < nums.length
            leftValue = nums[left - 1] if left > 0 else 0
            rightValue = nums[right + 1] if right < numsSize-1 else 0
            if leftValue < rightValue:
                right += 1
                minValue = min(minValue, nums[right])
            else:
                left -= 1
                minValue = min(minValue, nums[left])

            retVal = max(retVal, minValue*(right-left+1))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[1, 4, 3, 7, 4, 5], [5, 5, 4, 5, 4, 1, 1, 1]], [3, 0]):
            # /* Example
            #  *  Input: nums = [1,4,3,7,4,5], k = 3
            #  *  Output: 15
            #  *
            #  *  Input: nums = [5,5,4,5,4,1,1,1], k = 0
            #  *  Output: 20
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.maximumScore(nums, k)
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
