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
    def maxRemoval(self, nums: List[int], queries: List[List[int]]) -> int:
        retVal = -1

        queries.sort(key=lambda x: x[0])
        queriesSize = len(queries)

        heap = []

        numsSize = len(nums)
        deltaArray = [0] * (numsSize + 1)
        operations = 0

        j = 0
        for i, num in enumerate(nums):
            operations += deltaArray[i]

            while (j < queriesSize) and (queries[j][0] == i):
                heappush(heap, -queries[j][1])
                j += 1

            while (operations < num) and heap and (-heap[0] >= i):
                operations += 1
                deltaArray[-heappop(heap) + 1] -= 1

            if operations < num:
                return retVal

        retVal = len(heap)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, queries in zip([[2, 0, 2], [1, 1, 1, 1], [1, 2, 3, 4]],
                                 [[[0, 2], [0, 2], [1, 1]], [[1, 3], [0, 2], [1, 3], [1, 2]], [[0, 3]]]):
            # /* Example
            #  *  Input: nums = [2,0,2], queries = [[0,2],[0,2],[1,1]]
            #  *  Output: 1
            #  *
            #  *  Input: nums = [1,1,1,1], queries = [[1,3],[0,2],[1,3],[1,2]]
            #  *  Output: 2
            #  *
            #  *  Input: nums = [1,2,3,4], queries = [[0,3]]
            #  *  Output: -1
            #  */
            logging.info("Input: nums = %s, queries = %s", nums, queries)

            retVal = pSolution.maxRemoval(nums, queries)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
