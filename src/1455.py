import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from copy import deepcopy
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
    def isPrefixOfWord(self, sentence: str, searchWord: str) -> int:
        retVal = -1

        words = sentence.split()
        for idx, word in enumerate(words):
            if word.startswith(searchWord):
                retVal = idx + 1
                break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for sentence, searchWord in zip(["i love eating burger", "this problem is an easy problem", "i am tired"],
                                        ["burg", "pro", "you"]):
            # /* Example
            #  *  Input: sentence = "i love eating burger", searchWord = "burg"
            #  *  Output: 4
            #  *
            #  *  Input: sentence = "this problem is an easy problem", searchWord = "pro"
            #  *  Output: 2
            #  *
            #  *  Input: sentence = "i am tired", searchWord = "you"
            #  *  Output: -1
            #  */
            logging.info("Input: sentence = \"%s\", searchWord = %s",
                         sentence, searchWord)

            retVal = pSolution.isPrefixOfWord(sentence, searchWord)
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
