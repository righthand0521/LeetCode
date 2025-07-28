import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from math import ceil
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
    def isPossible(self, maxBallsInBag, nums, maxOperations) -> bool:
        retVal = True  # We can split the balls within the allowed operations, return True

        totalOperations = 0
        for num in nums:
            # Calculate the number of operations needed to split this bag
            operations = ceil(num / maxBallsInBag) - 1
            totalOperations += operations

            # If total operations exceed maxOperations, return False
            if totalOperations > maxOperations:
                retVal = False
                break

        return retVal

    def minimumSize(self, nums: List[int], maxOperations: int) -> int:
        retVal = 0

        # Perform binary search to find the optimal maxBallsInBag
        left = 1
        right = max(nums)
        while left < right:
            middle = (left + right) // 2

            # Check if a valid distribution is possible with the current middle value
            if self.isPossible(middle, nums, maxOperations):
                # If possible, try a smaller value (shift right to middle)
                right = middle
            else:
                # If not possible, try a larger value (shift left to middle + 1)
                left = middle + 1

        retVal = left  # Return the smallest possible value for maxBallsInBag

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, maxOperations in zip([[9], [2, 4, 8, 2]], [2, 4]):
            # /* Example
            #  *  Input: nums = [9], maxOperations = 2
            #  *  Output: 3
            #  *
            #  *  Input: nums = [2,4,8,2], maxOperations = 4
            #  *  Output: 2
            #  */
            logging.info("Input: nums = %s, maxOperations = %s", nums, maxOperations)

            retVal = pSolution.minimumSize(nums, maxOperations)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
