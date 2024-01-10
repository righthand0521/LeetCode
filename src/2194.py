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
    def cellsInRange(self, s: str) -> List[str]:
        retVal = []

        # s.length == 5
        # 'A' <= s[0] <= s[3] <= 'Z'
        # '1' <= s[1] <= s[4] <= '9'
        for row in range(ord(s[0]), ord(s[3])+1):
            for col in range(ord(s[1]), ord(s[4])+1):
                cell = chr(row) + chr(col)
                retVal.append(cell)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["K1:L2", "A1:F1"]:
            # /* Example
            # *  Input: s = "K1:L2"
            # *  Output: ["K1", "K2", "L1", "L2"]
            # *
            # *  Input: s = "A1:F1"
            # *  Output: ["A1", "B1", "C1", "D1", "E1", "F1"]
            # */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.cellsInRange(s)
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
