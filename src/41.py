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
    def firstMissingPositive(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        seen = [False] * (numsSize + 1)
        for num in nums:
            if 0 < num <= numsSize:
                seen[num] = True

        for i in range(1, numsSize + 1):
            if seen[i] == False:
                retVal = i
                return retVal
        retVal = numsSize + 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, 2, 0], [3, 4, -1, 1], [7, 8, 9, 11, 12], [2, 1]]:
            # /* Example
            #  *  Input: nums = [1,2,0]
            #  *  Output: 3
            #  *
            #  *  Input: nums = [3,4,-1,1]
            #  *  Output: 2
            #  *
            #  *  Input: nums = [7,8,9,11,12]
            #  *  Output: 1
            #  *
            #  *  Input: nums = [2, 1]
            #  *  Output: 3
            #  */
            logging.info("Input: height = %s", nums)

            retVal = pSolution.firstMissingPositive(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
