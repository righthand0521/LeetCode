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
    def mergeAlternately(self, word1: str, word2: str) -> str:
        retVal = ""

        idx1 = 0
        len1 = len(word1)
        idx2 = 0
        len2 = len(word2)
        while idx1 < len1 or idx2 < len2:
            if idx1 < len1:
                retVal += word1[idx1]
                idx1 += 1
            if idx2 < len2:
                retVal += word2[idx2]
                idx2 += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for word1, word2 in zip(["abc", "ab", "abcd"], ["pqr", "pqrs", "pq"]):
            # /* Example
            #  *  Input: word1 = "abc", word2 = "pqr"
            #  *  Output: "apbqcr"
            #  *
            #  *  Input: word1 = "ab", word2 = "pqrs"
            #  *  Output: "apbqrs"
            #  *
            #  *  Input: word1 = "abcd", word2 = "pq"
            #  *  Output: "apbqcd"
            #  */
            logging.info("Input: word1 = \"%s\", word2 = \"%s\"", word1, word2)

            retVal = pSolution.mergeAlternately(word1, word2)
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
