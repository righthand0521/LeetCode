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
    def divideArray(self, nums: List[int], k: int) -> List[List[int]]:
        retVal = []

        numsSize = len(nums)
        if (numsSize % 3) != 0:
            return retVal

        nums.sort()
        for i in range(0, numsSize, 3):
            if (nums[i+2] - nums[i]) > k:
                retVal = []
                break
            retVal.append([nums[i], nums[i+1], nums[i+2]])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[1, 3, 4, 8, 7, 9, 3, 5, 1], [1, 3, 3, 2, 7, 3],
                            [15, 13, 12, 13, 12, 14, 12, 2, 3, 13, 12, 14, 14, 13, 5, 12, 12, 2, 13, 2, 2]],
                           [2, 3, 2]):
            # /* Example
            #  *  Input: nums = [1,3,4,8,7,9,3,5,1], k = 2
            #  *  Output: [[1,1,3],[3,4,5],[7,8,9]]
            #  *
            #  *  Input: nums = [1,3,3,2,7,3], k = 3
            #  *  Output: []
            #  *
            #  *  Input: nums = [15,13,12,13,12,14,12,2,3,13,12,14,14,13,5,12,12,2,13,2,2], k = 2
            #  *  Output: []
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.divideArray(nums, k)
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
