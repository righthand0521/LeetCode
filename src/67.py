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
    def addBinary(self, a: str, b: str) -> str:
        retVal = ""

        carry = 0
        aIdx = len(a) - 1
        bIdx = len(b) - 1
        while (aIdx >= 0) and (bIdx >= 0):
            value = int(a[aIdx]) + int(b[bIdx]) + carry
            retVal = str(value % 2) + retVal
            carry = value // 2
            aIdx -= 1
            bIdx -= 1
        while (aIdx >= 0):
            value = int(a[aIdx]) + carry
            retVal = str(value % 2) + retVal
            carry = value // 2
            aIdx -= 1
        while (bIdx >= 0):
            value = int(b[bIdx]) + carry
            retVal = str(value % 2) + retVal
            carry = value // 2
            bIdx -= 1
        if carry == 1:
            retVal = "1" + retVal

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for a, b in zip(["11", "1010"], ["1", "1011"]):
            # /* Example
            #  *  Input: a = "11", b = "1"
            #  *  Output: "100"
            #  *
            #  *  Input: a = "1010", b = "1011"
            #  *  Output: "10101"
            #  */
            logging.info("Input: a = \"%s\", b = \"%s\"", a, b)

            retVal = pSolution.addBinary(a, b)
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
