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
    def __init__(self) -> None:
        self.letters = 3  # s consists of only the letters 'a', 'b', and 'c'.

    def takeCharacters(self, s: str, k: int) -> int:
        retVal = -1

        sSize = len(s)

        # Count total occurrences
        count = [0] * self.letters
        for c in s:
            count[ord(c) - ord("a")] += 1

        # Check if we have enough characters
        for i in range(self.letters):
            if count[i] < k:
                return retVal

        # Find the longest window that leaves k of each character outside
        window = [0] * self.letters
        maxWindow = 0
        left = 0
        for right in range(sSize):
            window[ord(s[right]) - ord("a")] += 1

            # Shrink window if we take too many characters
            while ((left <= right) and
                   ((count[0] - window[0] < k) or (count[1] - window[1] < k) or (count[2] - window[2] < k))):
                window[ord(s[left]) - ord("a")] -= 1
                left += 1

            maxWindow = max(maxWindow, right - left + 1)

        retVal = sSize - maxWindow

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, k in zip(["aabaaaacaabc", "a"], [2, 1]):
            # /* Example
            #  *  Input: s = "aabaaaacaabc", k = 2
            #  *  Output: 8
            #  *
            #  *  Input: s = "a", k = 1
            #  *  Output: -1
            #  */
            logging.info("Input: s = \"%s\", k = %s", s, k)

            retVal = pSolution.takeCharacters(s, k)
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
