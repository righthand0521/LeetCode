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


def guess(num: int) -> int:
    retVal = 0

    if num > pick:
        retVal = -1
    elif num < pick:
        retVal = 1

    return retVal


# The guess API is already defined for you.
# @param num, your guess
# @return -1 if num is higher than the picked number
#          1 if num is lower than the picked number
#          otherwise return 0
# def guess(num: int) -> int:
class Solution:
    def guessNumber(self, n: int) -> int:
        retVal = 0

        left = 1
        right = n
        while (left <= right):
            middle = left + ((right - left) // 2)

            ret = guess(middle)
            if ret == 0:
                retVal = middle
                break
            elif ret == -1:
                right = middle - 1
            elif ret == 1:
                left = middle + 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        global pick
        pSolution = Solution()
        for n, pick in zip([10, 1, 2], [6, 1, 1]):
            # /* Example
            #  *  Input: n = 10, pick = 6
            #  *  Output: 6
            #  *
            #  *  Input: n = 1, pick = 1
            #  *  Output: 1
            #  *
            #  *  Input: n = 2, pick = 1
            #  *  Output: 1
            #  */
            logging.info("Input: n = %s, pick = %s", n, pick)

            retVal = pSolution.guessNumber(n)
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
