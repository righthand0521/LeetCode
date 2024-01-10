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
    def largestVariance(self, s: str) -> int:
        retVal = 0

        pos = defaultdict(list)
        for i, ch in enumerate(s):
            pos[ch].append(i)

        for c0, pos0 in pos.items():
            for c1, pos1 in pos.items():
                if c0 == c1:
                    continue

                i = 0
                j = 0
                f = 0
                g = float("-inf")
                while i < len(pos0) or j < len(pos1):
                    if (j == len(pos1)) or (i < len(pos0) and pos0[i] < pos1[j]):
                        f = max(f, 0) + 1
                        g += 1
                        i += 1
                    else:
                        g = max(f, g, 0) - 1
                        f = max(f, 0) - 1
                        j += 1
                    retVal = max(retVal, g)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["aababbb", "abcde"]:
            # /* Example
            #  *  Input: s = "aababbb"
            #  *  Output: 3
            #  *
            #  *  Input: s = "abcde"
            #  *  Output: 0
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.largestVariance(s)
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
