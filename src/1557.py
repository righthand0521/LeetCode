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
    def findSmallestSetOfVertices(self, n: int, edges: List[List[int]]) -> List[int]:
        retVal = []

        incoming = [0] * n
        for edge in edges:
            incoming[edge[1]] += 1

        for i in range(n):
            if incoming[i] == 0:
                retVal.append(i)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, edges in zip([6, 5],
                            [[[0, 1], [0, 2], [2, 5], [3, 4], [4, 2]],
                             [[0, 1], [2, 1], [3, 1], [1, 4], [2, 4]]]):
            # /* Example
            #  *  Input: n = 6, edges = [[0,1],[0,2],[2,5],[3,4],[4,2]]
            #  *  Output: [0,3]
            #  *
            #  *  Input: n = 5, edges = [[0,1],[2,1],[3,1],[1,4],[2,4]]
            #  *  Output: [0,2,3]
            #  */
            logging.info("Input: n = %s, edges = %s", n, edges)

            retVal = pSolution.findSmallestSetOfVertices(n, edges)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
