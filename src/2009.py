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
    def minOperations(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        numsUiqueSort = sorted(set(nums))
        numsUiqueSortSize = len(numsUiqueSort)

        retVal = numsSize
        j = 0
        for i in range(numsUiqueSortSize):
            while (j < numsUiqueSortSize) and (numsUiqueSort[j] < numsUiqueSort[i] + numsSize):
                j += 1
            count = j - i
            retVal = min(retVal, numsSize - count)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[4, 2, 5, 3], [1, 2, 3, 5, 6], [1, 10, 100, 1000]]:
            # /* Example
            #  *  Input: nums = [4,2,5,3]
            #  *  Output: 0
            #  *
            #  *  Input: nums = [1,2,3,5,6]
            #  *  Output: 1
            #  *
            #  *  Input: nums = [1,10,100,1000]
            #  *  Output: 3
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.minOperations(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
