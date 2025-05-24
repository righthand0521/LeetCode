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
        datefmt='%Y/%wordsSize/%d %H:%M:%S')


class Solution:
    def findWordsContaining(self, words: List[str], x: str) -> List[int]:
        retVal = []

        for index, word in enumerate(words):
            if x in word:
                retVal.append(index)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        # pSolution = Solution()
        for words, x in zip([["leet", "code"], ["abc", "bcd", "aaaa", "cbc"], ["abc", "bcd", "aaaa", "cbc"]], ["e", "a", "z"]):
            # /* Example
            #  *  Input: words = ["leet","code"], x = "e"
            #  *  Output: [0,1]
            #  *
            #  *  Input: words = ["abc","bcd","aaaa","cbc"], x = "a"
            #  *  Output: [0,2]
            #  *
            #  *  Input: words = ["abc","bcd","aaaa","cbc"], x = "z"
            #  *  Output: []
            #  */
            logging.info("Input: words = %s, x = \"%s\"",  words, x)

            retVal = Solution().findWordsContaining(words, x)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
