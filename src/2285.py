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
    def maximumImportance(self, n: int, roads: List[List[int]]) -> int:
        retVal = 0

        degree = [0] * n
        for edge in roads:
            degree[edge[0]] += 1
            degree[edge[1]] += 1
        degree.sort()

        value = 1
        for d in degree:
            retVal += (value * d)
            value += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, roads in zip([5, 5], [[[0, 1], [1, 2], [2, 3], [0, 2], [1, 3], [2, 4]], [[0, 3], [2, 4], [1, 3]]]):
            # /* Example
            #  *  Input: n = 5, roads = [[0,1],[1,2],[2,3],[0,2],[1,3],[2,4]]
            #  *  Output: 43
            #  *
            #  *  Input: n = 5, roads = [[0,3],[2,4],[1,3]]
            #  *  Output: 20
            #  */
            logging.info("Input: n = %s, roads = %s", n, roads)

            retVal = pSolution.maximumImportance(n, roads)
            logging.info("Output: %d", retVal)

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
