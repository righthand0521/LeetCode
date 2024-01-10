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
    def winnerOfGame(self, colors: str) -> bool:
        retVal = False

        colorsSize = len(colors)

        Alice = 0
        Bob = 0
        for i in range(1, colorsSize-1):
            # The number of moves available to Alice is the number of times the substring "AAA" appears.
            # The number of moves available to Bob is the number of times the substring "BBB" appears.
            if (colors[i] == colors[i-1]) and (colors[i] == colors[i+1]):
                if colors[i] == 'A':
                    Alice += 1
                elif colors[i] == 'B':
                    Bob += 1
        if Alice > Bob:
            retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for colors in ["AAABABB", "AA", "ABBBBBBBAAA"]:
            # /* Example
            #  *  Input: colors = "AAABABB"
            #  *  Output: true
            #  *
            #  *  Input: colors = "AA"
            #  *  Output: false
            #  *
            #  *  Input: colors = "ABBBBBBBAAA"
            #  *  Output: false
            #  */
            logging.info("Input: colors = \"%s\"", colors)

            retVal = pSolution.winnerOfGame(colors)
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
