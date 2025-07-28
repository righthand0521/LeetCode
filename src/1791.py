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
    def findCenter(self, edges: List[List[int]]) -> int:
        retVal = 0

        degreeCount = defaultdict(int)
        for u, v in edges:
            degreeCount[u] += 1
            degreeCount[v] += 1

        edgesSize = len(edges)
        for key in degreeCount:
            if degreeCount[key] == edgesSize:
                retVal = key
                break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for edges in [[[1, 2], [2, 3], [4, 2]], [[1, 2], [5, 1], [1, 3], [1, 4]]]:
            # /* Example
            #  *  Input: edges = [[1,2],[2,3],[4,2]]
            #  *  Output: 2
            #  *
            #  *  Input: edges = [[1,2],[5,1],[1,3],[1,4]]
            #  *  Output: 1
            #  */
            logging.info("Input: edges = %s", edges)

            retVal = pSolution.findCenter(edges)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
