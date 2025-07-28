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
    def search(self, height, monoStack):
        retVal = -1

        left = 0
        right = len(monoStack) - 1
        while left <= right:
            middle = (left + right) // 2
            if monoStack[middle][0] > height:
                retVal = max(retVal, middle)
                left = middle + 1
            else:
                right = middle - 1

        return retVal

    def leftmostBuildingQueries(self, heights: List[int], queries: List[List[int]]) -> List[int]:
        retVal = []

        queriesSize = len(queries)
        retVal = [-1 for _ in range(queriesSize)]

        heightsSize = len(heights)
        newQueries = [[] for _ in range(heightsSize)]

        for i in range(queriesSize):
            a = queries[i][0]
            b = queries[i][1]
            if a > b:
                a, b = b, a

            if (heights[b] > heights[a]) or (a == b):
                retVal[i] = b
            else:
                newQueries[b].append((heights[a], i))

        monoStack = []
        for i in range(heightsSize - 1, -1, -1):
            monoStackSize = len(monoStack)
            for a, b in newQueries[i]:
                position = self.search(a, monoStack)
                if (position < monoStackSize) and (position >= 0):
                    retVal[b] = monoStack[position][1]

            while monoStack and (monoStack[-1][0] <= heights[i]):
                monoStack.pop()
            monoStack.append((heights[i], i))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for heights, queries in zip([[6, 4, 8, 5, 2, 7], [5, 3, 8, 2, 6, 1, 4, 6]],
                                    [[[0, 1], [0, 3], [2, 4], [3, 4], [2, 2]], [[0, 7], [3, 5], [5, 2], [3, 0], [1, 6]]]):
            # /* Example
            #  *  Input: heights = [6,4,8,5,2,7], queries = [[0,1],[0,3],[2,4],[3,4],[2,2]]
            #  *  Output: [2,5,-1,5,2]
            #  *
            #  *  Input: heights = [5,3,8,2,6,1,4,6], queries = [[0,7],[3,5],[5,2],[3,0],[1,6]]
            #  *  Output: [7,6,-1,4,6]
            #  */
            logging.info("Input: heights = %s, queries = %s", heights, queries)

            retVal = pSolution.leftmostBuildingQueries(heights, queries)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
