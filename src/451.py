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
    def frequencySort(self, s: str) -> str:
        retVal = ""

        hashTable = defaultdict(int)
        for c in s:
            hashTable[c] += 1
        sortHashTable = sorted(hashTable.items(), key=lambda kv: kv[1], reverse=True)

        for key, value in sortHashTable:
            for _ in range(value):
                retVal += key

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["tree", "cccaaa", "Aabb"]:
            # /* Example
            #  *  Input: s = "tree"
            #  *  Output: "eert"
            #  *
            #  *  Input: s = "cccaaa"
            #  *  Output: "aaaccc"
            #  *
            #  *  Input: s = "Aabb"
            #  *  Output: "bbAa"
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.frequencySort(s)
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
