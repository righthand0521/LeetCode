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
    def reorganizeString(self, s: str) -> str:
        retVal = ""

        count = defaultdict(int)
        for c in s:
            count[c] += 1
        count = sorted(count.items(), key=lambda kv: kv[1], reverse=True)

        sSize = len(s)
        if count[0][1] > ((sSize + 1) // 2):
            return retVal

        retVal = [""] * sSize
        idx = 0
        for key, value in count:
            for i in range(value):
                retVal[idx] = key
                idx += 2
                if idx >= sSize:
                    idx = 1
        retVal = "".join(retVal)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["aab", "aaab"]:
            # /* Example
            #  *  Input: s = "aab"
            #  *  Output: "aba"
            #  *
            #  *  Input: s = "aaab"
            #  *  Output: ""
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.reorganizeString(s)
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
