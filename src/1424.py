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
    def findDiagonalOrder(self, nums: List[List[int]]) -> List[int]:
        retVal = []

        numsSize = len(nums)

        queue = deque([(0, 0)])
        while queue:
            row, col = queue.popleft()
            retVal.append(nums[row][col])

            if (col == 0) and (row + 1 < numsSize):
                queue.append((row + 1, col))

            numsColSize = len(nums[row])
            if col + 1 < numsColSize:
                queue.append((row, col + 1))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [
            [[1, 2, 3], [4, 5, 6], [7, 8, 9]],
            [[1, 2, 3, 4, 5], [6, 7], [8], [9, 10, 11], [12, 13, 14, 15, 16]]
        ]:
            # /* Example
            #  *  Input: nums = [[1,2,3],[4,5,6],[7,8,9]]
            #  *  Output: [1,4,2,7,5,3,8,6,9]
            #  *
            #  *  Input: nums = [[1,2,3,4,5],[6,7],[8],[9,10,11],[12,13,14,15,16]]
            #  *  Output: [1,6,2,8,7,3,9,4,12,10,5,13,11,14,15,16]
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.findDiagonalOrder(nums)
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
