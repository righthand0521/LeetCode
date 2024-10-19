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
    def findKthBit(self, n: int, k: int) -> str:
        retVal = '0'

        if n == 1:
            return retVal

        length = 1 << n
        if k < length // 2:
            retVal = self.findKthBit(n - 1, k)
        elif k == length // 2:
            retVal = '1'
        else:
            correspondingBit = self.findKthBit(n - 1, length - k)
            retVal = "1" if correspondingBit == "0" else "0"

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, k in zip([3, 4], [1, 11]):
            # /* Example
            #  *  Input: n = 3, k = 1
            #  *  Output: "0"
            #  *
            #  *  Input: n = 4, k = 11
            #  *  Output: "1"
            #  */
            logging.info("Input: n = %s, k = %s", n, k)

            retVal = pSolution.findKthBit(n, k)
            logging.info("Output: \"%s\"", retVal)

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
