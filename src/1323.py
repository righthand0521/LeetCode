import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop
from math import log10


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
    def maximum69Number(self, num: int) -> int:
        retVal = num

        base = 0
        if retVal != 0:
            base = 10 ** int(log10(retVal))

        while base > 0:
            if (retVal // base) % 10 == 6:
                retVal += 3 * base
                break
            base = base // 10

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for num in [9669, 9996, 9999]:
            # /* Example
            #  *  Input: num = 9669
            #  *  Output: 9969
            #  *
            #  *  Input: num = 9996
            #  *  Output: 9999
            #  *
            #  *  Input: num = 9999
            #  *  Output: 9999
            #  */
            logging.info("Input: num = %d", num)

            retVal = pSolution.maximum69Number(num)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
