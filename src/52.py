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
    def backtrack(self, n: int, row: int, columns: set, diagonal1: set, diagonal2: set) -> int:
        retVal = 0

        if row == n:
            retVal = 1
            return retVal

        for i in range(n):
            if i in columns or row - i in diagonal1 or row + i in diagonal2:
                continue

            columns.add(i)
            diagonal1.add(row - i)
            diagonal2.add(row + i)
            retVal += self.backtrack(n, row + 1, columns, diagonal1, diagonal2)
            columns.remove(i)
            diagonal1.remove(row - i)
            diagonal2.remove(row + i)

        return retVal

    def totalNQueens(self, n: int) -> int:
        retVal = 0

        columns = set()
        diagonal1 = set()
        diagonal2 = set()
        retVal = self.backtrack(n, 0, columns, diagonal1, diagonal2)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [4, 1]:
            # /* Example
            #  *  Input: n = 4
            #  *  Output: 2
            #  *
            #  *  Input: n = 1
            #  *  Output: 1
            #  */
            logging.info("Input: n = %s", n)

            retVal = pSolution.totalNQueens(n)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
