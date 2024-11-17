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
    def shortestSubarray(self, nums: List[int], k: int) -> int:
        retVal = -1

        numsSize = len(nums)

        prefixSums = [0] * (numsSize + 1)
        for i in range(1, numsSize + 1):
            prefixSums[i] = prefixSums[i - 1] + nums[i - 1]

        candidateIndices = deque()
        shortestSubarrayLength = float("inf")
        for i in range(numsSize + 1):
            # Remove candidates from front of deque where subarray sum meets target
            while ((candidateIndices) and (prefixSums[i] - prefixSums[candidateIndices[0]] >= k)):
                shortestSubarrayLength = min(shortestSubarrayLength, i - candidateIndices.popleft())

            # Maintain monotonicity by removing indices with larger prefix sums
            while ((candidateIndices) and (prefixSums[i] <= prefixSums[candidateIndices[-1]])):
                candidateIndices.pop()

            # Add current index to candidates
            candidateIndices.append(i)

        if shortestSubarrayLength != float("inf"):
            retVal = shortestSubarrayLength

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[1], [1, 2], [2, -1, 2]], [1, 4, 3]):
            # /* Example
            #  *  Input: nums = [1], k = 1
            #  *  Output: 1
            #  *
            #  *  Input: nums = [1,2], k = 4
            #  *  Output: -1
            #  *
            #  *  Input: nums = [2,-1,2], k = 3
            #  *  Output: 3
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.shortestSubarray(nums, k)
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
