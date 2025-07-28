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
    def continuousSubarrays(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        right = 0
        left = 0
        curMin = nums[right]
        curMax = nums[right]
        windowLen = 0
        for right in range(numsSize):
            curMin = min(curMin, nums[right])
            curMax = max(curMax, nums[right])
            if curMax - curMin <= 2:
                continue

            # Add subarrays from previous valid window
            windowLen = right - left
            retVal += windowLen * (windowLen + 1) // 2
            # Start new window at current position
            left = right
            curMin = nums[right]
            curMax = nums[right]
            # Expand left boundary while maintaining condition
            while (left > 0) and (abs(nums[right] - nums[left - 1]) <= 2):
                left -= 1
                curMin = min(curMin, nums[left])
                curMax = max(curMax, nums[left])
            # Remove overcounted subarrays if left boundary expanded
            if left < right:
                windowLen = right - left
                retVal -= windowLen * (windowLen + 1) // 2

        # Add subarrays from final window
        windowLen = right - left + 1
        retVal += windowLen * (windowLen + 1) // 2

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[5, 4, 2, 4], [1, 2, 3], [65, 66, 67, 66, 66, 65, 64, 65, 65, 64]]:
            # /* Example
            #  *  Input: nums = [5,4,2,4]
            #  *  Output: 8
            #  *
            #  *  Input: nums = [1,2,3]
            #  *  Output: 6
            #  *
            #  *  Input: nums = [65,66,67,66,66,65,64,65,65,64]
            #  *  Output: 43
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.continuousSubarrays(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
