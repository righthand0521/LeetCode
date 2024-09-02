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
    def chalkReplacer(self, chalk: List[int], k: int) -> int:
        retVal = 0

        total = sum(chalk)
        k = k % total

        for key, value in enumerate(chalk):
            if value > k:
                retVal = key
                break
            k -= value

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for chalk, k in zip([[5, 1, 5], [3, 4, 1, 2]], [22, 25]):
            # /* Example
            #  *  Input: chalk = [5,1,5], k = 22
            #  *  Output: 0
            #  *
            #  *  Input: chalk = [3,4,1,2], k = 25
            #  *  Output: 1
            #  */
            logging.info("Input: chalk = %s, k = %s", chalk, k)

            retVal = pSolution.chalkReplacer(chalk, k)
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
