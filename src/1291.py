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
    def sequentialDigits(self, low: int, high: int) -> List[int]:
        retVal = []

        for i in range(1, 10):  # 10 <= low <= high <= 10^9
            num = i
            for j in range(i+1, 10):
                num = 10 * num + j
                if (num >= low) and (num <= high):
                    retVal.append(num)
        retVal.sort()

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for low, high in zip([100, 1000], [300, 13000]):
            # /* Example
            #  *  Input: low = 100, high = 300
            #  *  Output: [123,234]
            #  *
            #  *  Input: low = 1000, high = 13000
            #  *  Output: [1234,2345,3456,4567,5678,6789,12345]
            #  */
            logging.info("Input: low = %s, high = %s", low, high)

            retVal = pSolution.sequentialDigits(low, high)
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
