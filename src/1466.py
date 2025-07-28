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
    def minReorder(self, n: int, connections: List[List[int]]) -> int:
        retVal = 0

        adjacent = [[] for i in range(n)]
        backAdjacent = [[] for i in range(n)]
        for src, dest in connections:
            adjacent[src].append(dest)
            backAdjacent[dest].append(src)

        # Breadth-First Search
        bfsQueue = deque([0])
        visit = set()
        while bfsQueue:
            src = bfsQueue.popleft()
            visit.add(src)

            for dest in adjacent[src]:
                if dest not in visit:
                    bfsQueue.append(dest)
                    retVal += 1

            for dest in backAdjacent[src]:
                if dest not in visit:
                    bfsQueue.append(dest)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, connections in zip([6, 5, 3],
                                  [[[0, 1], [1, 3], [2, 3], [4, 0], [4, 5]],
                                   [[1, 0], [1, 2], [3, 2], [3, 4]],
                                   [[1, 0], [2, 0]]]):
            # /* Example
            #  *  Input: n = 6, connections = [[0,1],[1,3],[2,3],[4,0],[4,5]]
            #  *  Output: 3
            #  *
            #  *  Input: n = 5, connections = [[1,0],[1,2],[3,2],[3,4]]
            #  *  Output: 2
            #  *
            #  *  Input: n = 3, connections = [[1,0],[2,0]]
            #  *  Output: 0
            #  */
            logging.info("Input: n = %d, connections = %s", n, connections)

            retVal = pSolution.minReorder(n, connections)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
