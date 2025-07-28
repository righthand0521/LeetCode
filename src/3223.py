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
    def minimumLength(self, s: str) -> int:
        retVal = 0

        # s consists only of lowercase English letters.
        charFrequency = [0] * 26
        for current_char in s:
            charFrequency[ord(current_char) - ord("a")] += 1

        for frequency in charFrequency:
            if frequency == 0:
                continue

            if frequency % 2 == 0:
                retVal += 2
            else:
                retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["abaacbcbb", "aa"]:
            # /* Example
            #  *  Input: s = "abaacbcbb"
            #  *  Output: 5
            #  *
            #  *  Input: s = "aa"
            #  *  Output: 2
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
