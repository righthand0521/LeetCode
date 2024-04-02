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
    def reverseBits(self, n: int) -> int:
        retVal = 0

        for _ in range(32):
            retVal = (retVal << 1) | (n & 0x1)
            n >>= 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in ["00000010100101000001111010011100", "11111111111111111111111111111101"]:
            # /* Example
            #  *  Input: n = 00000010100101000001111010011100
            #  *  Output:    964176192 (00111001011110000010100101000000)
            #  *
            #  *  Input: n = 11111111111111111111111111111101
            #  *  Output:   3221225471 (10111111111111111111111111111111)
            #  */
            logging.info("Input: n = %s", n)

            retVal = pSolution.reverseBits(int(n, 2))
            logging.info("Output: %s (%s)", retVal, format(retVal, '08b'))

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
