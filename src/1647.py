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
    def minDeletions(self, s: str) -> int:
        retVal = 0

        frequency = Counter(s).most_common()

        hashSet = set()
        for key, value in frequency:
            for i in range(value, 0, -1):
                if i not in hashSet:
                    hashSet.add(i)
                    break
                retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["aab", "aaabbbcc", "ceabaacb", "abc", "aaab", "abcabc"]:
            # /* Example
            #  *  Input: s = "aab"
            #  *  Output: 0
            #  *
            #  *  Input: s = "aaabbbcc"
            #  *  Output: 2
            #  *
            #  *  Input: s = "ceabaacb"
            #  *  Output: 2
            #  *
            #  *  Input: s = "abc"
            #  *  Output: 2
            #  *
            #  *  Input: s = "aaab"
            #  *  Output: 0
            #  *
            #  *  Input: s = "abcabc"
            #  *  Output: 3
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.minDeletions(s)
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
