import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop
from copy import deepcopy


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
    def minMaxDifference(self, num: int) -> int:
        retVal = 0

        numMaxStr = str(num)
        numMaxStrSize = len(numMaxStr)
        idx = 0
        while (idx < numMaxStrSize) and (numMaxStr[idx] == "9"):
            idx += 1
        if idx < numMaxStrSize:
            numMaxStr = numMaxStr.replace(numMaxStr[idx], "9")

        numMinStr = str(num)
        numMinStr = numMinStr.replace(numMinStr[0], "0")

        retVal = int(numMaxStr) - int(numMinStr)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for num in [11891, 90]:
            # /* Example
            #  *  Input: num = 11891
            #  *  Output: 99009
            #  *
            #  *  Input: num = 90
            #  *  Output: 99
            #  */
            logging.info("Input: num = %s", num)

            retVal = pSolution.minMaxDifference(num)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
