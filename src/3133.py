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
    def minEnd(self, n: int, x: int) -> int:
        retVal = x

        n -= 1  # Reducing n by 1 to exclude x from the iteration
        mask = 1
        while n > 0:  # Step 1: Iterate while n > 0, using mask for bit positions
            if (mask & x) == 0:  # Step 2: If the corresponding bit in x is 0
                # Set the bit in result based on least significant bit of n
                retVal |= ((n & 1) * mask)
                # Shift n right by 1 to process next bit
                n >>= 1
            mask <<= 1  # Shift mask left by 1 for next iteration

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, x in zip([3, 2], [4, 7]):
            # /* Example
            #  *  Input: n = 3, x = 4
            #  *  Output: 6
            #  *
            #  *  Input: n = 2, x = 7
            #  *  Output: 15
            #  */
            logging.info("Input: n = %s, x = %s", n, x)

            retVal = pSolution.minEnd(n, x)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
