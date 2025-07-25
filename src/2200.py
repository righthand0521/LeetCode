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
    def findKDistantIndices(self, nums: List[int], key: int, k: int) -> List[int]:
        retVal = []

        numsSize = len(nums)
        left = 0
        for j in range(numsSize):
            if nums[j] != key:
                continue
            right = max(left, j - k)
            left = min(numsSize - 1, j + k) + 1
            for i in range(right, left):
                retVal.append(i)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, key, k in zip([[3, 4, 9, 1, 3, 9, 5], [2, 2, 2, 2, 2]], [9, 2], [1, 2]):
            # /* Example
            #  *  Input: nums = [3,4,9,1,3,9,5], key = 9, k = 1
            #  *  Output: [1,2,3,4,5,6]
            #  *
            #  *  Input: nums = [2,2,2,2,2], key = 2, k = 2
            #  *  Output: [0,1,2,3,4]
            #  */
            logging.info("Input: nums = %s, key = %s, k = %s", nums, key, k)

            retVal = pSolution.findKDistantIndices(nums, key, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
