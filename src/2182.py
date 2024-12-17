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
    def repeatLimitedString(self, s: str, repeatLimit: int) -> str:
        retVal = ""

        frequency = Counter(s)
        maxHeap = []
        for char, count in frequency.items():
            maxHeap.append((-ord(char), count))
        heapify(maxHeap)

        while maxHeap:
            char, count = heappop(maxHeap)
            char = chr(-char)
            use = min(count, repeatLimit)
            retVal += (char * use)

            if (count > use) and maxHeap:
                nextChar, nextCount = heappop(maxHeap)
                retVal += chr(-nextChar)
                if nextCount > 1:
                    heappush(maxHeap, (nextChar, nextCount - 1))
                heappush(maxHeap, (-ord(char), count - use))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, repeatLimit in zip(["cczazcc", "aababab"], [3, 2]):
            # /* Example
            #  *  Input: s = "cczazcc", repeatLimit = 3
            #  *  Output: "zzcccac"
            #  *
            #  *  Input: s = "aababab", repeatLimit = 2
            #  *  Output: "bbabaa"
            #  */
            logging.info("Input: s = \"%s\", repeatLimit = %s", s, repeatLimit)

            retVal = pSolution.repeatLimitedString(s, repeatLimit)
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
