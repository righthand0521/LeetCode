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
    def areSentencesSimilar(self, sentence1: str, sentence2: str) -> bool:
        retVal = False

        words1 = list(sentence1.split())
        words2 = list(sentence2.split())

        while words1 and words2 and (words1[0] == words2[0]):
            words1.pop(0)
            words2.pop(0)

        while words1 and words2 and (words1[-1] == words2[-1]):
            words1.pop(-1)
            words2.pop(-1)

        if (not words1) or (not words2):
            retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for sentence1, sentence2 in zip(["My name is Haley", "of", "Eating right now", "Luky"],
                                        ["My Haley", "A lot of words", "Eating", "Lucccky"]):
            # /* Example
            #  *  Input: sentence1 = "My name is Haley", sentence2 = "My Haley"
            #  *  Output: true
            #  *
            #  *  Input: sentence1 = "of", sentence2 = "A lot of words"
            #  *  Output: false
            #  *
            #  *  Input: sentence1 = "Eating right now", sentence2 = "Eating"
            #  *  Output: true
            #  *
            #  *  Input: sentence1 = "Luky", sentence2 = "Lucccky"
            #  *  Output: false
            #  */
            logging.info("Input: sentence1 = \"%s\", sentence2 = \"%s\"", sentence1, sentence2)

            retVal = pSolution.areSentencesSimilar(sentence1, sentence2)
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
