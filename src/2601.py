import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from math import sqrt
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
    def primeSubOperation(self, nums: List[int]) -> bool:
        retVal = False

        # Store the sieve array.
        maxElement = max(nums)
        sieve = [1] * (maxElement + 1)
        sieve[1] = 0
        for i in range(2, int(sqrt(maxElement + 1)) + 1):
            if sieve[i] == 1:
                for j in range(i * i, maxElement + 1, i):
                    sieve[j] = 0

        # Start by storing the currValue as 1, and the initial index as 0.
        currValue = 1

        numsSize = len(nums)
        i = 0
        while i < numsSize:
            # Store the difference needed to make nums[i] equal to currValue.
            difference = nums[i] - currValue
            # If difference is less than 0, then nums[i] is already less than currValue. Return false in this case.
            if difference < 0:
                return retVal

            # If the difference is prime or zero, then nums[i] can be made equal to currValue.
            # Otherwise, try for the next currValue.
            if sieve[difference] or difference == 0:
                i += 1
                currValue += 1
            else:
                currValue += 1

        retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[4, 9, 6, 10], [6, 8, 11, 12], [5, 8, 3]]:
            # /* Example
            #  *  Input: nums = [4,9,6,10]
            #  *  Output: true
            #  *
            #  *  Input: nums = [6,8,11,12]
            #  *  Output: true
            #  *
            #  *  Input: nums = [5,8,3]
            #  *  Output: false
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.primeSubOperation(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
