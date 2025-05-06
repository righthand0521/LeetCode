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
    def buildArray(self, nums: List[int]) -> List[int]:
        retVal = [0 for _ in nums]

        numsSize = len(nums)
        for i in range(numsSize):
            retVal[i] = nums[nums[i]]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[0, 2, 1, 5, 3, 4], [5, 0, 1, 2, 3, 4]]:
            # /* Example
            #  *  Input: nums = [0,2,1,5,3,4]
            #  *  Output: [0,1,2,4,5,3]
            #  *
            #  *  Input: nums = [5,0,1,2,3,4]
            #  *  Output: [4,5,0,1,2,3]
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.buildArray(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
