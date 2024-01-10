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
    def __init__(self):
        self.MODULO = 10 ** 9 + 7

    def numberOfWays(self, corridor: str) -> int:
        retVal = 1

        count = 0
        previous = -1
        for index, value in enumerate(corridor):
            if value == "S":
                count += 1

                if (count >= 3) and (count % 2 == 1):
                    retVal = (retVal * (index - previous)) % self.MODULO

                previous = index

        if (count < 2) or (count % 2 == 1):
            retVal = 0

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for corridor in ["SSPPSPS", "PPSPSP", "S"]:
            # /* Example
            #  *  Input: corridor = "SSPPSPS"
            #  *  Output: 3
            #  *
            #  *  Input: corridor = "PPSPSP"
            #  *  Output: 1
            #  *
            #  *  Input: corridor = "S"
            #  *  Output: 0
            #  */
            logging.info("Input: corridor = \"%s\"", corridor)

            retVal = pSolution.numberOfWays(corridor)
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
