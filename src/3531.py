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
    def countCoveredBuildings(self, n: int, buildings: List[List[int]]) -> int:
        retVal = 0

        maxRow = [0] * (n + 1)
        minRow = [n + 1] * (n + 1)
        maxCol = [0] * (n + 1)
        minCol = [n + 1] * (n + 1)
        for building in buildings:
            x = building[0]
            y = building[1]
            maxRow[y] = max(maxRow[y], x)
            minRow[y] = min(minRow[y], x)
            maxCol[x] = max(maxCol[x], y)
            minCol[x] = min(minCol[x], y)

        for building in buildings:
            x = building[0]
            y = building[1]
            if ((x > minRow[y]) and (x < maxRow[y]) and (y > minCol[x]) and (y < maxCol[x])):
                retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, buildings in [
            [3, [[1, 2], [2, 2], [3, 2], [2, 1], [2, 3]]],
            [3, [[1, 1], [1, 2], [2, 1], [2, 2]]],
            [5, [[1, 3], [3, 2], [3, 3], [3, 5], [5, 3]]]
        ]:
            # /* Example
            #  *  Input: n = 3, buildings = [[1,2],[2,2],[3,2],[2,1],[2,3]]
            #  *  Output: 1
            #  *
            #  *  Input: n = 3, buildings = [[1,1],[1,2],[2,1],[2,2]]
            #  *  Output: 0
            #  *
            #  *  Input: n = 5, buildings = [[1,3],[3,2],[3,3],[3,5],[5,3]]
            #  *  Output: 1
            #  */
            logging.info("Input: n = %s, buildings = %s", n, buildings)

            retVal = pSolution.countCoveredBuildings(n, buildings)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
