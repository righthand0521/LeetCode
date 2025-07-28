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
    def halvesAreAlike(self, s: str) -> bool:
        retVal = True

        vowels = "aeiouAEIOU"

        count = 0
        head = 0
        tail = len(s) - 1
        while head < tail:
            if s[head] in vowels:
                count += 1
            head += 1

            if s[tail] in vowels:
                count -= 1
            tail -= 1

        if count != 0:
            retVal = False

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["book", "textbook"]:
            # /* Example
            #  *  Input: s = "book"
            #  *  Output: true
            #  *
            #  *  Input: s = "textbook"
            #  *  Output: false
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.halvesAreAlike(s)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
