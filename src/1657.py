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
    def closeStrings(self, word1: str, word2: str) -> bool:
        retVal = False

        word1Size = len(word1)
        word2Size = len(word2)
        if word1Size != word2Size:
            return retVal

        hashTable1 = Counter(word1)
        hashTable2 = Counter(word2)

        if hashTable1.keys() != hashTable2.keys():
            return retVal

        if sorted(hashTable1.values()) != sorted(hashTable2.values()):
            return retVal

        retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for word1, word2 in zip(["abc", "a", "cabbba", "uau"], ["bca", "aa", "abbccc", "ssx"]):
            # /* Example
            #  *  Input: word1 = "abc", word2 = "bca"
            #  *  Output: true
            #  *
            #  *  Input: word1 = "a", word2 = "aa"
            #  *  Output: false
            #  *
            #  *  Input: word1 = "cabbba", word2 = "abbccc"
            #  *  Output: true
            #  *
            #  *  Input: word1 = "uau", word2 = "ssx"
            #  *  Output: false
            #  */
            logging.info("Input: word1 = \"%s\", word2 = \"%s\"", word1, word2)

            retVal = pSolution.closeStrings(word1, word2)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
