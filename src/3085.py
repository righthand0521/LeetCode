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
    def minimumDeletions(self, word: str, k: int) -> int:
        retVal = 0

        frequency = defaultdict(int)
        for c in word:
            frequency[c] += 1

        retVal = len(word)
        for a in frequency.values():
            deleted = 0
            for b in frequency.values():
                if a > b:
                    deleted += b
                elif b > a + k:
                    deleted += (b - (a + k))
            retVal = min(retVal, deleted)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for word, k in zip(["aabcaba", "dabdcbdcdcd", "aaabaaa"], [0, 2, 2]):
            # /* Example
            #  *  Input: word = "aabcaba", k = 0
            #  *  Output: 3
            #  *
            #  *  Input: word = "dabdcbdcdcd", k = 2
            #  *  Output: 2
            #  *
            #  *  Input: word = "aaabaaa", k = 2
            #  *  Output: 1
            #  */
            logging.info("Input: word = \"%s\", k = %s", word, k)

            retVal = pSolution.minimumDeletions(word, k)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
