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
    def maxSumOfThreeSubarrays(self, nums: List[int], k: int) -> List[int]:
        retVal = []

        # Variables to track the best indices for one, two, and three subarray configurations
        bestSingleStart = 0
        bestDoubleStart = [0, k]
        bestTripleStart = [0, k, k * 2]

        # Compute the initial sums for the first three subarrays
        currentWindowSumSingle = sum(nums[:k])
        currentWindowSumDouble = sum(nums[k: k * 2])
        currentWindowSumTriple = sum(nums[k * 2: k * 3])

        # Track the best sums found so far
        bestSingleSum = currentWindowSumSingle
        bestDoubleSum = currentWindowSumSingle + currentWindowSumDouble
        bestTripleSum = currentWindowSumSingle + currentWindowSumDouble + currentWindowSumTriple

        # Sliding window pointers for the subarrays
        singleStartIndex = 1
        doubleStartIndex = k + 1
        tripleStartIndex = k * 2 + 1

        numsSize = len(nums)
        while tripleStartIndex <= numsSize - k:
            # Update the sums using the sliding window technique
            currentWindowSumSingle = currentWindowSumSingle - \
                nums[singleStartIndex - 1] + nums[singleStartIndex + k - 1]
            currentWindowSumDouble = currentWindowSumDouble - \
                nums[doubleStartIndex - 1] + nums[doubleStartIndex + k - 1]
            currentWindowSumTriple = currentWindowSumTriple - \
                nums[tripleStartIndex - 1] + nums[tripleStartIndex + k - 1]

            # Update the best single subarray start index if a better sum is found
            if currentWindowSumSingle > bestSingleSum:
                bestSingleStart = singleStartIndex
                bestSingleSum = currentWindowSumSingle

            # Update the best double subarray start indices if a better sum is found
            if currentWindowSumDouble + bestSingleSum > bestDoubleSum:
                bestDoubleStart[0] = bestSingleStart
                bestDoubleStart[1] = doubleStartIndex
                bestDoubleSum = currentWindowSumDouble + bestSingleSum

            # Update the best triple subarray start indices if a better sum is found
            if currentWindowSumTriple + bestDoubleSum > bestTripleSum:
                bestTripleStart[0] = bestDoubleStart[0]
                bestTripleStart[1] = bestDoubleStart[1]
                bestTripleStart[2] = tripleStartIndex
                bestTripleSum = currentWindowSumTriple + bestDoubleSum

            # Move the sliding windows forward
            singleStartIndex += 1
            doubleStartIndex += 1
            tripleStartIndex += 1

        # Return the starting indices of the three subarrays with the maximum sum
        retVal = bestTripleStart

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[1, 2, 1, 2, 6, 7, 5, 1], [1, 2, 1, 2, 1, 2, 1, 2, 1]], [2, 2]):
            # /* Example
            #  *  Input: nums = [1,2,1,2,6,7,5,1], k = 2
            #  *  Output: [0,3,5]
            #  *
            #  *  Input: nums = [1,2,1,2,1,2,1,2,1], k = 2
            #  *  Output: [0,2,4]
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.maxSumOfThreeSubarrays(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
