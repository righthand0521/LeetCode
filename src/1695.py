import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop


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
    def maximumUniqueSubarray(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        prefixsum = [0] * (numsSize + 1)
        frequency = {}
        previous = 0
        for i in range(numsSize):
            prefixsum[i + 1] = prefixsum[i] + nums[i]
            previous = max(previous, frequency.get(nums[i], 0))
            retVal = max(retVal, prefixsum[i + 1] - prefixsum[previous])
            frequency[nums[i]] = i + 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[4, 2, 4, 5, 6], [5, 2, 1, 2, 5, 2, 1, 2, 5]]:
            # /* Example
            #  *  Input: nums = [4,2,4,5,6]
            #  *  Output: 17
            #  *
            #  *  Input: nums = [5,2,1,2,5,2,1,2,5]
            #  *  Output: 8
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.maximumUniqueSubarray(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
