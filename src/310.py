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
    def findMinHeightTrees(self, n: int, edges: List[List[int]]) -> List[int]:
        retVal = []

        if n == 1:
            retVal = [0]
            return retVal

        adjacency = [[] for _ in range(n)]
        degree = [0] * n
        for src, dst in edges:
            adjacency[src].append(dst)
            adjacency[dst].append(src)
            degree[src] += 1
            degree[dst] += 1

        for key, value in enumerate(degree):
            if value == 1:
                retVal.append(key)

        remainNodes = n
        while remainNodes > 2:
            remainNodes -= len(retVal)
            tmp = retVal
            retVal = []
            for x in tmp:
                for y in adjacency[x]:
                    degree[y] -= 1
                    if degree[y] == 1:
                        retVal.append(y)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, edges in zip([4, 6], [[[1, 0], [1, 2], [1, 3]], [[3, 0], [3, 1], [3, 2], [3, 4], [5, 4]]]):
            # /* Example
            #  *  Input: n = 4, edges = [[1,0],[1,2],[1,3]]
            #  *  Output: [1]
            #  *
            #  *  Input: n = 6, edges = [[3,0],[3,1],[3,2],[3,4],[5,4]]
            #  *  Output: [3,4]
            #  */
            logging.info("Input: n = %s, edges = %s", n, edges)

            retVal = pSolution.findMinHeightTrees(n, edges)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
