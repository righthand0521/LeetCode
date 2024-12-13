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
    def findScore(self, nums):
        retVal = 0

        numsSize = len(nums)

        heap = []
        for index, num in enumerate(nums):
            heappush(heap, (num, index))

        marked = [False] * numsSize
        while heap:
            num, index = heappop(heap)

            if marked[index] == True:
                continue

            retVal += num
            marked[index] = True
            # mark adjacent elements if they exist
            if index - 1 >= 0:
                marked[index - 1] = True
            if index + 1 < numsSize:
                marked[index + 1] = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[2, 1, 3, 4, 5, 2], [2, 3, 5, 1, 3, 2]]:
            # /* Example
            #  *  Input: nums = [2,1,3,4,5,2]
            #  *  Output: 7
            #  *
            #  *  Input: nums = [2,3,5,1,3,2]
            #  *  Output: 5
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.findScore(nums)
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
