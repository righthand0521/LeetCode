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
    def queryResults(self, limit: int, queries: List[List[int]]) -> List[int]:
        retVal = []

        queriesSize = len(queries)

        colorMap = {}
        ballMap = {}
        for i in range(queriesSize):
            ball, color = queries[i]

            # Check if ball is already colored
            if ball in ballMap:
                # Decrement count of the previous color on the ball
                prevColor = ballMap[ball]
                colorMap[prevColor] -= 1

                # If there are no balls with previous color left, remove color from color map
                if colorMap[prevColor] == 0:
                    del colorMap[prevColor]

            ballMap[ball] = color  # Set color of ball to the new color
            colorMap[color] = colorMap.get(color, 0) + 1  # Increment the count of the new color

            retVal.append(len(colorMap))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for limit, queries in zip([4, 4], [[[1, 4], [2, 5], [1, 3], [3, 4]], [[0, 1], [1, 2], [2, 2], [3, 4], [4, 5]]]):
            # /* Example
            #  *  Input: limit = 4, queries = [[1,4],[2,5],[1,3],[3,4]]
            #  *  Output: [1,2,2,3]
            #  *
            #  *  Input: limit = 4, queries = [[0,1],[1,2],[2,2],[3,4],[4,5]]
            #  *  Output: [1,2,2,3,4]
            #  */
            logging.info("Input: limit = %s, queries = %s", limit, queries)

            retVal = pSolution.queryResults(limit, queries)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
