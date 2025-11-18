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
    def isOneBitCharacter(self, bits: List[int]) -> bool:
        retVal = False

        parity = bits.pop()
        while (bits) and (bits.pop()):
            parity ^= 1
        retVal = (parity == 0)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for bits in [[1, 0, 0], [1, 1, 1, 0]]:
            # /* Example:
            #  *  Input: bits = [1,0,0]
            #  *  Output: true
            #  *
            #  *  Input: bits = [1,1,1,0]
            #  *  Output: false
            #  */
            logging.info("Input: bits = %s", bits)

            retVal = pSolution.isOneBitCharacter(bits)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
