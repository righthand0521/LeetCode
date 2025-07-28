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
    def __init__(self):
        self.method = 1

        if self.method == 1:
            print("Math")
        elif self.method == 2:
            print("Brute force")
        print()

    def addDigits(self, num: int) -> int:
        retVal = 0

        if self.method == 1:
            # /* https://en.wikipedia.org/wiki/Digital_root
            #  *  abcd
            #  *  = a * 1000 + b * 100 + c * 10 + d
            #  *  = a * (999 + 1) + b * (99 + 1) + c * (9 + 1) + d
            #  *  = (a * 999 + b * 99 + c * 9) + (a + b + c + d)
            #  */
            if num != 0:
                retVal = num % 9
                if retVal == 0:
                    retVal = 9
        elif self.method == 2:
            retVal = num
            while num >= 10:
                retVal = 0
                tmp = num
                while tmp > 0:
                    retVal += (tmp % 10)
                    tmp //= 10
                num = retVal

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for num in [38, 0]:
            # /* Example
            #  *  Input: num = 38
            #  *  Output: 2
            #  *
            #  *  Input: num = 0
            #  *  Output: 0
            #  */
            logging.info("Input: num = %s", num)

            retVal = pSolution.addDigits(num)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
