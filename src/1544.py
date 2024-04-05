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
    def makeGood(self, s: str) -> str:
        retVal = ""

        for c in s:
            if (retVal != "") and (ord(retVal[-1]) == ord(c) ^ 32):
                retVal = retVal[:-1]
            else:
                retVal += c

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["leEeetcode", "abBAcC", "s"]:
            # /* Example
            #  *  Input: s = "leEeetcode"
            #  *  Output: "leetcode"
            #  *
            #  *  Input: s = "abBAcC"
            #  *  Output: ""
            #  *
            #  *  Input: s = "s"
            #  *  Output: "s"
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.makeGood(s)
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
