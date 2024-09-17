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
    def uncommonFromSentences(self, s1: str, s2: str) -> List[str]:
        retVal = []

        hashTable = Counter()
        for word in s1.split():
            hashTable[word] += 1
        for word in s2.split():
            hashTable[word] += 1

        for key, value in hashTable.items():
            if value == 1:
                retVal.append(key)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s1, s2 in zip(["this apple is sweet", "apple apple"], ["this apple is sour", "banana"]):
            # /* Example
            #  *  Input: s1 = "this apple is sweet", s2 = "this apple is sour"
            #  *  Output: ["sweet","sour"]
            #  *
            #  *  Input: s1 = "apple apple", s2 = "banana"
            #  *  Output: ["banana"]
            #  */
            logging.info("Input: s1 = \"%s\", s2 = \"%s\"", s1, s2)

            retVal = pSolution.uncommonFromSentences(s1, s2)
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
