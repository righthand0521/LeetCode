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
    def minimumLength(self, s: str) -> int:
        retVal = 0

        left = 0
        right = len(s) - 1
        while (left < right) and (s[left] == s[right]):
            equal = s[left]
            while (left <= right) and (s[left] == equal):
                left += 1
            while (left <= right) and (s[right] == equal):
                right -= 1
        retVal = right - left + 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["ca", "cabaabac", "aabccabba"]:
            # /* Example
            #  *  Input: s = "ca"
            #  *  Output: 2
            #  *
            #  *  Input: s = "cabaabac"
            #  *  Output: 0
            #  *
            #  *  Input: s = "aabccabba"
            #  *  Output: 3
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.minimumLength(s)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
