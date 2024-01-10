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
    def checkStraightLine(self, coordinates: List[List[int]]) -> bool:
        retVal = True

        coordinatesSize = len(coordinates)
        if coordinatesSize == 2:
            return retVal

        # // https://en.wikipedia.org/wiki/Cross_product
        for i in range(2, coordinatesSize):
            v1x = coordinates[i-1][0] - coordinates[i-2][0]
            v1y = coordinates[i-1][1] - coordinates[i-2][1]
            v2x = coordinates[i][0] - coordinates[i-1][0]
            v2y = coordinates[i][1] - coordinates[i-1][1]
            if v1x * v2y != v1y * v2x:
                retVal = False
                break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for coordinates in [[[1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7]],
                            [[1, 1], [2, 2], [3, 4], [4, 5], [5, 6], [7, 7]],
                            [[1, 2], [1, 3], [1, 4], [1, 5], [1, 6], [6, 7]],
                            [[2, 1], [4, 2], [6, 3]]]:
            # /* Example
            #  *  Input: coordinates = [[1,2],[2,3],[3,4],[4,5],[5,6],[6,7]]
            #  *  Output: true
            #  *
            #  *  Input: coordinates = [[1,1],[2,2],[3,4],[4,5],[5,6],[7,7]]
            #  *  Output: false
            #  *
            #  *  Input: coordinates = [[1, 2],[1, 3],[1, 4],[1, 5],[1, 6],[6, 7]]
            #  *  Output: false
            #  *
            #  *  Input: coordinates = [[2, 1],[4, 2],[6, 3]]
            #  *  Output: true
            #  */
            logging.info("Input: coordinates = %s", coordinates)

            retVal = pSolution.checkStraightLine(coordinates)
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
