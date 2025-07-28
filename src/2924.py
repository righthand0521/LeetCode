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
    def findChampion(self, n: int, edges: List[List[int]]) -> int:
        retVal = -1

        indegree = [0] * n
        for edge in edges:
            indegree[edge[1]] += 1

        for i in range(n):
            if indegree[i] != 0:
                continue

            if retVal == -1:
                retVal = i
            else:
                retVal = -1
                break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, edges in zip([3, 4], [[[0, 1], [1, 2]], [[0, 2], [1, 3], [1, 2]]]):
            # /* Example
            #  *  Input: n = 3, edges = [[0,1],[1,2]]
            #  *  Output: 0
            #  *
            #  *  Input: n = 4, edges = [[0,2],[1,3],[1,2]]
            #  *  Output: -1
            #  */
            logging.info("Input: n = %s, edges = %s", n, edges)

            retVal = pSolution.findChampion(n, edges)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
