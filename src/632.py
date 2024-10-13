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
    def smallestRange(self, nums: List[List[int]]) -> List[int]:
        retVal = []

        numsSize = len(nums)

        # Merge all lists with their list index
        merged = []
        for i in range(numsSize):
            for num in nums[i]:
                merged.append((num, i))
        merged.sort()
        mergedSize = len(merged)

        # Two pointers to track the smallest range
        freq = defaultdict(int)
        rangeStart = 0
        rangeEnd = float("inf")
        count = 0
        left = 0
        for right in range(mergedSize):
            freq[merged[right][1]] += 1
            if freq[merged[right][1]] == 1:
                count += 1

            # When all lists are represented, try to shrink the window
            while count == numsSize:
                curRange = merged[right][0] - merged[left][0]
                if curRange < rangeEnd - rangeStart:
                    rangeStart = merged[left][0]
                    rangeEnd = merged[right][0]

                freq[merged[left][1]] -= 1
                if freq[merged[left][1]] == 0:
                    count -= 1

                left += 1

        retVal = [rangeStart, rangeEnd]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[[4, 10, 15, 24, 26], [0, 9, 12, 20], [5, 18, 22, 30]], [[1, 2, 3], [1, 2, 3], [1, 2, 3]]]:
            # /* Example
            #  *  Input: nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
            #  *  Output: [20,24]
            #  *
            #  *  Input: nums = [[1,2,3],[1,2,3],[1,2,3]]
            #  *  Output: [1,1]
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.smallestRange(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info = True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info = True)
        pass

    sys.exit(0)
