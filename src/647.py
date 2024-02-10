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
    def countSubstrings(self, s: str) -> int:
        retVal = 0

        sSize = len(s)

        for i in range(2 * sSize - 1):
            left = i // 2
            right = (i // 2) + (i % 2)
            while ((left >= 0) and (right < sSize) and (s[left] == s[right])):
                left -= 1
                right += 1
                retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["abc", "aaa"]:
            # /* Example
            #  *  Input: s = "abc"
            #  *  Output: 3
            #  *
            #  *  Input: s = "aaa"
            #  *  Output: 6
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.countSubstrings(s)
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
