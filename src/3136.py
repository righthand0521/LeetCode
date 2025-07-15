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
    def isValid(self, word: str) -> bool:
        retVal = False

        wordSize = len(word)
        if wordSize < 3:
            return retVal

        hasVowel = False
        hasConsonant = False
        for c in word:
            if c.isalpha():
                if c.lower() in "aeiou":
                    hasVowel = True
                else:
                    hasConsonant = True
            elif c.isdigit():
                continue
            else:
                return retVal
        retVal = hasVowel and hasConsonant

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for word in ["234Adas", "b3", "a3$e"]:
            # /* Example
            #  *  Input: word = "234Adas"
            #  *  Output: true
            #  *
            #  *  Input: word = "b3"
            #  *  Output: false
            #  *
            #  *  Input: word = "a3$e"
            #  *  Output: false
            #  */
            logging.info("Input: word = \"%s\"", word)

            retVal = pSolution.isValid(word)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
