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
    def reverse(self, nums: List[int], left: int, right: int) -> None:
        while left < right:
            nums[left], nums[right] = nums[right], nums[left]
            left += 1
            right -= 1

    def nextPermutation(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        numsSize = len(nums)

        i = numsSize - 2
        while (i >= 0) and (nums[i] >= nums[i + 1]):
            i -= 1
        if i < 0:
            self.reverse(nums, 0, numsSize - 1)
        else:
            j = numsSize - 1
            while (j > i) and (nums[j] <= nums[i]):
                j -= 1
            nums[i], nums[j] = nums[j], nums[i]
            self.reverse(nums, i + 1, numsSize - 1)


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, 2, 3], [3, 2, 1], [1, 1, 5]]:
            # /* Example
            #  *  Input: nums = [1,2,3]
            #  *  Output: [1,3,2]
            #  *
            #  *  Input: nums = [3,2,1]
            #  *  Output: [1,2,3]
            #  *
            #  *  Input: nums = [1,1,5]
            #  *  Output: [1,5,1]
            #  */
            logging.info("Input: nums = %s", nums)

            pSolution.nextPermutation(nums)
            logging.info("Output: %s", nums)

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
