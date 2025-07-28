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
    def restoreArray(self, adjacentPairs: List[List[int]]) -> List[int]:
        retVal = []

        graph = defaultdict(list)
        for x, y in adjacentPairs:
            graph[x].append(y)
            graph[y].append(x)

        root = None
        for num in graph:
            if len(graph[num]) == 1:
                root = num
                break
        retVal = [root]

        curr = root
        prev = None
        while len(retVal) < len(graph):
            for neighbor in graph[curr]:
                if neighbor != prev:
                    retVal.append(neighbor)
                    prev = curr
                    curr = neighbor
                    break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for adjacentPairs in [[[2, 1], [3, 4], [3, 2]], [[4, -2], [1, 4], [-3, 1]], [[100000, -100000]]]:
            # /* Example
            #  *  Input: adjacentPairs = [[2,1],[3,4],[3,2]]
            #  *  Output: [1,2,3,4]
            #  *
            #  *  Input: adjacentPairs = [[4,-2],[1,4],[-3,1]]
            #  *  Output: [-2,4,1,-3]
            #  *
            #  *  Input: adjacentPairs = [[100000,-100000]]
            #  *  Output: [100000,-100000]
            #  */
            logging.info("Input: adjacentPairs = %s", adjacentPairs)

            retVal = pSolution.restoreArray(adjacentPairs)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
