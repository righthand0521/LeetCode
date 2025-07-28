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
    def reverse(self, x: int) -> int:
        retVal = 0

        absoluteValue = abs(x)
        while absoluteValue > 0:
            retVal = (retVal * 10) + (absoluteValue % 10)
            absoluteValue //= 10
        if x < 0:
            retVal = -(retVal)

        # // If reversing x causes the value to go outside the signed 32 - bit integer range[-2 ^ 31, 2 ^ 31 - 1],
        # // then return 0.
        if (retVal > (2**31-1)) or (retVal < (-2**31)):
            retVal = 0

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for x in [123, -123, 120, 2**31-1, -2**31]:
            # /* Example
            #  *  Input: x = 123
            #  *  Output: 321
            #  *
            #  *  Input: x = -123
            #  *  Output: -321
            #  *
            #  *  Input: x = 120
            #  *  Output: 21
            #  *
            #  *  Input: x = 2147483647
            #  *  Output: 0
            #  *
            #  *  Input: x = -2147483648
            #  *  Output: 0
            #  */
            logging.info("Input: x = %s", x)

            retVal = pSolution.reverse(x)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
