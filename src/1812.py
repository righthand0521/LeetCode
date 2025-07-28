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
    def squareIsWhite(self, coordinates: str) -> bool:
        if (len(coordinates) != 2):
            return False

        row = ord(coordinates[0]) - ord('a')
        col = ord(coordinates[1]) - ord('0')
        if (((row % 2) == 0) and ((col % 2) == 0)):
            return True
        elif (((row % 2) == 1) and ((col % 2) == 1)):
            return True

        return False


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for coordinates in ["a1", "h3", "c7"]:
            # /* Example
            #  *  Input: coordinates = "a1"
            #  *  Output: false
            #  *
            #  *  Input: coordinates = "h3"
            #  *  Output: true
            #  *
            #  *  Input: coordinates = "c7"
            #  *  Output: false
            #  */
            logging.info("Input: coordinates = \"%s\"", coordinates)

            retVal = pSolution.squareIsWhite(coordinates)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
