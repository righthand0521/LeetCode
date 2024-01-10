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
        self.numericCell = 10

    def knightDialer(self, n: int) -> int:
        retVal = 0

        jumps = [[4, 6], [6, 8], [7, 9], [4, 8], [3, 9, 0], [], [1, 7, 0], [2, 6], [1, 3], [2, 4]]

        previousDp = [1] * self.numericCell
        for _ in range(1, n):
            dp = [0] * self.numericCell

            for square in range(self.numericCell):
                sum = 0
                for nextSquare in jumps[square]:
                    sum = (sum + previousDp[nextSquare]) % self.MODULO

                dp[square] = sum

            previousDp = dp

        for square in range(self.numericCell):
            retVal = (retVal + previousDp[square]) % self.MODULO

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [1, 2, 3131]:
            # /* Example
            #  *  Input: n = 1
            #  *  Output: 10
            #  *
            #  *  Input: n = 2
            #  *  Output: 20
            #  *
            #  *  Input: n = 3131
            #  *  Output: 136006598
            #  */
            logging.info("Input: n = %s", n)

            retVal = pSolution.knightDialer(n)
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
