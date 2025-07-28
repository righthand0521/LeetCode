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
    def maximumCount(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        negative = 0
        zero = 0
        positive = 0
        for i in range(numsSize):
            if nums[i] < 0:
                negative += 1
            elif nums[i] == 0:
                zero += 1
            else:
                break
        positive = numsSize - negative - zero

        retVal = max(negative, positive)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[-2, -1, -1, 1, 2, 3], [-3, -2, -1, 0, 0, 1, 2], [5, 20, 66, 1314]]:
            # /* Example
            #  *  Input: nums = [-2,-1,-1,1,2,3]
            #  *  Output: 3
            #  *
            #  *  Input: nums = [-3,-2,-1,0,0,1,2]
            #  *  Output: 3
            #  *
            #  *  Input: nums = [5,20,66,1314]
            #  *  Output: 4
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.maximumCount(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
