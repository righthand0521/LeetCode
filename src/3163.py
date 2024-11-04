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
    def compressedString(self, word: str) -> str:
        retVal = ""

        wordSize = len(word)

        count = 1
        for i in range(1, wordSize):
            if (word[i] == word[i-1]) and (count < 9):
                count += 1
                continue
            retVal += (str(count) + word[i-1])
            count = 1
        retVal += (str(count) + word[wordSize-1])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for word in ["abcde", "aaaaaaaaaaaaaabb"]:
            # /* Example
            #  *  Input: word = "abcde"
            #  *  Output: "1a1b1c1d1e"
            #  *
            #  *  Input: word = "aaaaaaaaaaaaaabb"
            #  *  Output: "9a5a2b"
            #  */
            logging.info("Input: word = \"%s\"", word)

            retVal = pSolution.compressedString(word)
            logging.info("Output: \"%s\"", retVal)

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
