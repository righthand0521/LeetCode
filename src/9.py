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
    def isPalindrome(self, x: int) -> bool:
        retVal = False

        if x < 0:
            return retVal

        original = x
        palindrome = 0
        while x > 0:
            palindrome *= 10
            palindrome += x % 10
            x //= 10

        if original == palindrome:
            retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for x in [121, -121, 10, 1234567899]:
            # /* Example
            #  *  Input: x = 121
            #  *  Output: true
            #  *
            #  *  Input: x = -121
            #  *  Output: false
            #  *
            #  *  Input: x = 10
            #  *  Output: false
            #  *
            #  *  Input: x = 1234567899
            #  *  Output: false
            #  */
            logging.info("Input: x = %s", x)

            retVal = pSolution.isPalindrome(x)
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
