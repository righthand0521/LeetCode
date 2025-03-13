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
    def minZeroArray(self, nums: List[int], queries: List[List[int]]) -> int:
        retVal = 0

        numsSize = len(nums)
        queriesSize = len(queries)

        sum = 0
        differenceArray = [0] * (numsSize + 1)
        for index in range(numsSize):
            # Iterate through queries while current index of nums cannot equal zero
            while sum + differenceArray[index] < nums[index]:
                retVal += 1
                # Zero array isn't formed after all queries are processed
                if retVal > queriesSize:
                    retVal = -1
                    return retVal

                # Process start and end of range
                left, right, val = queries[retVal - 1]
                if right >= index:
                    differenceArray[max(left, index)] += val
                    differenceArray[right + 1] -= val

            # Update prefix sum at current index
            sum += differenceArray[index]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, queries in zip([[2, 0, 2], [4, 3, 2, 1]], [[[0, 2, 1], [0, 2, 1], [1, 1, 3]], [[1, 3, 2], [0, 2, 1]]]):
            # /* Example
            #  *  Input: nums = [2,0,2], queries = [[0,2,1],[0,2,1],[1,1,3]]
            #  *  Output: 2
            #  *
            #  *  Input: nums = [4,3,2,1], queries = [[1,3,2],[0,2,1]]
            #  *  Output: -1
            #  */
            logging.info("Input: nums = %s, queries = %s", nums, queries)

            retVal = pSolution.minZeroArray(nums, queries)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
