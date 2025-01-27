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
    def checkIfPrerequisite(self, numCourses: int, prerequisites: List[List[int]], queries: List[List[int]]) -> List[bool]:
        retVal = []

        isPrerequisite = [[False] * numCourses for _ in range(numCourses)]
        for edge in prerequisites:
            isPrerequisite[edge[0]][edge[1]] = True

        for intermediate in range(numCourses):
            for src in range(numCourses):
                for target in range(numCourses):
                    # If there is a path src -> intermediate and intermediate -> target, then src -> target exists as well
                    isPrerequisite[src][target] = isPrerequisite[src][target] or (
                        isPrerequisite[src][intermediate] and isPrerequisite[intermediate][target])

        for query in queries:
            retVal.append(isPrerequisite[query[0]][query[1]])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for numCourses, prerequisites, queries in zip(
                [2, 2, 3],
                [[[1, 0]], [], [[1, 2], [1, 0], [2, 0]]],
                [[[0, 1], [1, 0]], [[1, 0], [0, 1]], [[1, 0], [1, 2]]]
        ):
            # /* Example
            #  *  Input: numCourses = 2, prerequisites = [[1,0]], queries = [[0,1],[1,0]]
            #  *  Output: [false,true]
            #  *
            #  *  Input: numCourses = 2, prerequisites = [], queries = [[1,0],[0,1]]
            #  *  Output: [false,false]
            #  *
            #  *  Input: numCourses = 3, prerequisites = [[1,2],[1,0],[2,0]], queries = [[1,0],[1,2]]
            #  *  Output: [true,true]
            #  */
            logging.info("Input: numCourses = %s, prerequisites = %s, queries = %s", numCourses, prerequisites, queries)

            retVal = pSolution.checkIfPrerequisite(numCourses, prerequisites, queries)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
