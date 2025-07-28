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
    def isPathCrossing(self, path: str) -> bool:
        retVal = False

        moves = {
            "N": (0, 1),
            "S": (0, -1),
            "W": (-1, 0),
            "E": (1, 0)
        }

        visited = {(0, 0)}
        x = 0
        y = 0
        for direction in path:
            x += moves[direction][0]
            y += moves[direction][1]
            if (x, y) in visited:
                retVal = True
                break
            visited.add((x, y))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for path in ["NES", "NESWW"]:
            # /* Example
            #  *  Input: path = "NES"
            #  *  Output: false
            #  *
            #  *  Input: path = "NESWW"
            #  *  Output: true
            #  */
            logging.info("Input: path = \"%s\"", path)

            retVal = pSolution.isPathCrossing(path)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
