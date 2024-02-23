import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop
from copy import deepcopy


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
    def findCheapestPrice(self, n: int, flights: List[List[int]], src: int, dst: int, k: int) -> int:
        retVal = -1

        # https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm
        maxValue = float('inf')
        distance = [maxValue] * n
        distance[src] = 0
        for i in range(k+1):
            tmp = distance.copy()
            for start, end, price in flights:
                if distance[start] != maxValue:
                    tmp[end] = min(tmp[end], distance[start]+price)
            distance = tmp.copy()

        if distance[dst] != maxValue:
            retVal = distance[dst]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, flights, src, dst, k in zip([4, 3, 3],
                                           [[[0, 1, 100], [1, 2, 100], [2, 0, 100], [1, 3, 600], [2, 3, 200]],
                                            [[0, 1, 100], [1, 2, 100], [0, 2, 500]],
                                            [[0, 1, 100], [1, 2, 100], [0, 2, 500]]],
                                           [0, 0, 0],
                                           [3, 2, 2],
                                           [1, 1, 0]):
            # /* Example
            #  *  Input: n = 4, flights = [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]], src = 0, dst = 3, k = 1
            #  *  Output: 700
            #  *
            #  *  Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 1
            #  *  Output: 200
            #  *
            #  *  Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 0
            #  *  Output: 500
            #  */
            logging.info(
                "Input: n = %s, flights = %s, src = %s, dst = %s, k = %s", n, flights, src, dst, k)

            retVal = pSolution.findCheapestPrice(n, flights, src, dst, k)
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
