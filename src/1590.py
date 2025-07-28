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
    def minSubarray(self, nums: List[int], p: int) -> int:
        retVal = 0

        numsSize = len(nums)

        # Step 1: Calculate total sum and target remainder
        totalSum = 0
        for num in nums:
            totalSum = (totalSum + num) % p
        target = totalSum % p
        if target == 0:
            return retVal  # The array is already divisible by p

        # Step 2: Use a dict to track prefix sum mod p
        modMap = {0: -1}    # To handle the case where the whole prefix is the answer

        # Step 3: Iterate over the array
        retVal = numsSize
        currentSum = 0
        for i in range(numsSize):
            currentSum = (currentSum + nums[i]) % p

            needed = (currentSum - target + p) % p  # Calculate what we need to remove
            # If we have seen the needed remainder, we can consider this subarray
            if needed in modMap:
                retVal = min(retVal, i - modMap[needed])

            modMap[currentSum] = i  # Store the current remainder and index

        if retVal == numsSize:
            retVal = -1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, p in zip([[3, 1, 4, 2], [6, 3, 5, 2], [1, 2, 3]], [6, 9, 3]):
            # /* Example
            #  *  Input: nums = [3,1,4,2], p = 6
            #  *  Output: 1
            #  *
            #  *  Input: nums = [6,3,5,2], p = 9
            #  *  Output: 2
            #  *
            #  *  Input: nums = [1,2,3], p = 3
            #  *  Output: 0
            #  */
            logging.info("Input: nums = %s, p = %s", nums, p)

            retVal = pSolution.minSubarray(nums, p)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
