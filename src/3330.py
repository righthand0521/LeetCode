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
    def possibleStringCount(self, word: str) -> int:
        retVal = 1

        wordSize = len(word)
        for i in range(1, wordSize):
            if word[i-1] == word[i]:
                retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for word in ["abbcccc", "abcd", "aaaa"]:
            # /* Example
            #  *  Input: word = "abbcccc"
            #  *  Output: 5
            #  *
            #  *  Input: word = "abcd"
            #  *  Output: 1
            #  *
            #  *  Input: word = "aaaa"
            #  *  Output: 4
            #  */
            logging.info("Input: word = \"%s\"", word)

            retVal = pSolution.possibleStringCount(word)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
