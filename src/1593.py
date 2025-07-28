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
    def backtrack(self, s, start, seen):
        retVal = 0

        sSize = len(s)

        # Base case: If we reach the end of the string, return 0 (no more substrings to add)
        if start == sSize:
            return retVal

        # Try every possible substring starting from 'start'
        for end in range(start + 1, sSize + 1):
            substring = s[start:end]
            if substring not in seen:   # If the substring is unique
                # Add the substring to the seen set
                seen.add(substring)
                # Recursively count unique substrings from the next position
                retVal = max(retVal, 1 + self.backtrack(s, end, seen))
                # Backtrack: remove the substring from the seen set
                seen.remove(substring)

        return retVal

    def maxUniqueSplit(self, s: str) -> int:
        retVal = 0

        seen = set()
        retVal = self.backtrack(s, 0, seen)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["ababccc", "aba", "aa"]:
            # /* Example
            #  *  Input: s = "ababccc"
            #  *  Output: 5
            #  *
            #  *  Input: s = "aba"
            #  *  Output: 2
            #  *
            #  *  Input: s = "aa"
            #  *  Output: 1
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.maxUniqueSplit(s)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
