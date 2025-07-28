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
    def __init__(self) -> None:
        self.method = 1

    def countBits(self, n: int) -> List[int]:
        retVal = [0] * (n+1)

        for i in range(n+1):
            if self.method == 1:    # O(n)
                # /* f[i] = f[i/2] + i%2
                #  *  retVal[000] = 0
                #  *  retVal[001] = retVal[00] + (1%2) = 0 + 1 = 1
                #  *  retVal[010] = retVal[01] + (2%2) = 1 + 0 = 1
                #  *  retVal[011] = retVal[01] + (3%2) = 1 + 1 = 2
                #  *  retVal[100] = retVal[10] + (4%2) = 1 + 0 = 1
                #  *  retVal[101] = retVal[10] + (5%2) = 1 + 1 = 2
                #  *  retVal[110] = retVal[11] + (6%2) = 2 + 0 = 2
                #  *  retVal[111] = retVal[11] + (7%2) = 2 + 1 = 3
                #  */
                retVal[i] = retVal[i >> 1] + (i & 1)
            elif self.method == 2:  # O(n log n)
                tmp = i
                while tmp > 0:
                    if (tmp & 1) == 1:
                        retVal[i] += 1
                    tmp >>= 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [2, 5]:
            # /* Example
            #  *  Input: n = 2
            #  *  Output: [0,1,1]
            #  *
            #  *  Input: n = 5
            #  *  Output: [0,1,1,2,1,2]
            #  */
            logging.info("Input: n = %s", n)

            retVal = pSolution.countBits(n)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
