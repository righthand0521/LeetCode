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
    def addMode(self, nums: List[int], k: int, modes: set, value: int) -> None:
        modes.add(value)
        if value - k >= nums[0]:
            modes.add(value - k)
        if value + k <= nums[-1]:
            modes.add(value + k)

    def maxFrequency(self, nums: List[int], k: int, numOperations: int) -> int:
        retVal = 0

        nums.sort()

        numCount = defaultdict(int)
        modes = set()

        lastIndex = 0
        for i in range(len(nums)):
            if nums[i] == nums[lastIndex]:
                continue
            numCount[nums[lastIndex]] = i - lastIndex
            retVal = max(retVal, i - lastIndex)
            self.addMode(nums, k, modes, nums[lastIndex])
            lastIndex = i

        numCount[nums[lastIndex]] = len(nums) - lastIndex
        retVal = max(retVal, len(nums) - lastIndex)
        self.addMode(nums, k, modes, nums[lastIndex])

        for mode in sorted(modes):
            l = bisect_left(nums, mode - k)
            r = bisect_right(nums, mode + k) - 1
            if mode in numCount:
                temp = min(r - l + 1, numCount[mode] + numOperations)
            else:
                temp = min(r - l + 1, numOperations)
            retVal = max(retVal, temp)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k, numOperations in [[[1, 4, 5], 1, 2], [[5, 11, 20, 20], 5, 1]]:
            # /* Example
            #  *  Input: nums = [1,4,5], k = 1, numOperations = 2
            #  *  Output: 2
            #  *
            #  *  Input: nums = [5,11,20,20], k = 5, numOperations = 1
            #  *  Output: 2
            #  */
            logging.info("Input: nums = %s, k = %s, numOperations = %s", nums, k, numOperations)

            retVal = pSolution.maxFrequency(nums, k, numOperations)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
