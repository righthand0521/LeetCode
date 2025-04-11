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
    def countSymmetricIntegers(self, low: int, high: int) -> int:
        retVal = 0

        # 1 <= low <= high <= 10^4
        for num in range(low, high + 1):
            if num < 100:
                if num % 11 == 0:
                    retVal += 1
            elif 1000 <= num < 10000:
                left = num // 1000 + num % 1000 // 100
                right = num % 100 // 10 + num % 10
                if left == right:
                    retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for low, high in zip([1, 1200], [100, 1230]):
            # /* Example
            #  *  Input: low = 1, high = 100
            #  *  Output: 9
            #  *
            #  *  Input: low = 1200, high = 1230
            #  *  Output: 4
            #  */
            logging.info("Input: low = %s, high = %s", low, high)

            retVal = pSolution.countSymmetricIntegers(low, high)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
