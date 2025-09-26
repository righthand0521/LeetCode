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
    def triangleNumber(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        nums.sort()
        for i in range(numsSize):
            k = i
            for j in range(i + 1, numsSize):
                while ((k + 1 < numsSize) and (nums[k + 1] < nums[i] + nums[j])):
                    k += 1
                retVal += max(k - j, 0)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[2, 2, 3, 4], [4, 2, 3, 4]]:
            # /* Example
            #  *  Input: nums = [2,2,3,4]
            #  *  Output: 3
            #  *
            #  *  Input: nums = [4,2,3,4]
            #  *  Output: 4
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.triangleNumber(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
