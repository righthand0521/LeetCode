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
    def pivotIndex(self, nums: List[int]) -> int:
        retVal = -1

        numsSize = len(nums)

        sumLeft = [0] * numsSize
        sumLeft[0] = nums[0]
        for i in range(1, numsSize):
            sumLeft[i] = sumLeft[i - 1] + nums[i]

        sumRight = [0] * numsSize
        sumRight[numsSize - 1] = nums[numsSize - 1]
        for i in range(numsSize - 2, -1, -1):
            sumRight[i] = sumRight[i + 1] + nums[i]

        for i in range(numsSize):
            if sumLeft[i] == sumRight[i]:
                retVal = i
                break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, 7, 3, 6, 5, 6], [1, 2, 3], [2, 1, -1]]:
            # /* Example
            #  *  Input: nums = [1,7,3,6,5,6]
            #  *  Output: 3
            #  *
            #  *  Input: nums = [1,2,3]
            #  *  Output: -1
            #  *
            #  *  Input: nums = [2,1,-1]
            #  *  Output: 0
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.pivotIndex(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
