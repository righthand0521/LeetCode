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
    def longestSubarray(self, nums: List[int], limit: int) -> int:
        retVal = 0

        maxDeque = deque()
        minDeque = deque()
        numsSize = len(nums)
        left = 0
        right = 0
        for right in range(numsSize):
            # Maintain the maxDeque in decreasing order
            while (maxDeque) and (maxDeque[-1] < nums[right]):
                maxDeque.pop()
            maxDeque.append(nums[right])

            # Maintain the minDeque in increasing order
            while (minDeque) and (minDeque[-1] > nums[right]):
                minDeque.pop()
            minDeque.append(nums[right])

            # Check if the current window exceeds the limit
            while maxDeque[0] - minDeque[0] > limit:
                # Remove the elements that are out of the current window
                if maxDeque[0] == nums[left]:
                    maxDeque.popleft()
                if minDeque[0] == nums[left]:
                    minDeque.popleft()

                left += 1

            retVal = max(retVal, right - left + 1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, limit in zip([[8, 2, 4, 7], [10, 1, 2, 4, 7, 2], [4, 2, 2, 2, 4, 4, 2, 2]], [4, 5, 0]):
            # /* Example
            #  *  Input: nums = [8,2,4,7], limit = 4
            #  *  Output: 2
            #  *
            #  *  Input: nums = [10,1,2,4,7,2], limit = 5
            #  *  Output: 4
            #  *
            #  *  Input: nums = [4,2,2,2,4,4,2,2], limit = 0
            #  *  Output: 3
            #  */
            logging.info("Input: nums = %s, limit = %s", nums, limit)

            retVal = pSolution.longestSubarray(nums, limit)
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
