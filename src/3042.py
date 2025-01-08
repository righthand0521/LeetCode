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
    def countPrefixSuffixPairs(self, words: List[str]) -> int:
        retVal = 0

        wordsSize = len(words)
        for i in range(wordsSize):
            for j in range(i + 1, wordsSize):
                str1 = words[i]
                str2 = words[j]
                if len(str1) > len(str2):
                    continue

                if (str2.startswith(str1)) and (str2.endswith(str1)):
                    retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for words in [["a", "aba", "ababa", "aa"], ["pa", "papa", "ma", "mama"], ["abab", "ab"]]:
            # /* Example
            #  *  Input: words = ["a","aba","ababa","aa"]
            #  *  Output: 4
            #  *
            #  *  Input: words = ["pa","papa","ma","mama"]
            #  *  Output: 2
            #  *
            #  *  Input: words = ["abab","ab"]
            #  *  Output: 0
            #  */
            logging.info("Input: words = %s", words)

            retVal = pSolution.countPrefixSuffixPairs(words)
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
