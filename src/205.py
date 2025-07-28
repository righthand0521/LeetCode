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
    def isIsomorphic(self, s: str, t: str) -> bool:
        retVal = False

        sSize = len(s)
        tSize = len(t)
        if sSize != tSize:
            return retVal

        hashTableS = defaultdict()
        hashTableT = defaultdict()
        for i in range(sSize):
            if (s[i] in hashTableS) and (hashTableS[s[i]] != t[i]):
                return retVal
            elif (t[i] in hashTableT) and (hashTableT[t[i]] != s[i]):
                return retVal
            else:
                hashTableS[s[i]] = t[i]
                hashTableT[t[i]] = s[i]
        retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, t in zip(["egg", "foo", "paper", "badc", "abcdefghijklmnopqrstuvwxyzva"],
                        ["add", "bar", "title", "baba", "abcdefghijklmnopqrstuvwxyzck"]):
            # /* Example
            #  *  Input: s = "egg", t = "add"
            #  *  Output: true
            #  *
            #  *  Input: s = "foo", t = "bar"
            #  *  Output: false
            #  *
            #  *  Input: s = "paper", t = "title"
            #  *  Output: true
            #  *
            #  *  Input: s = "badc", t = "baba"
            #  *  Output: false
            #  *
            #  *  Input: s = "abcdefghijklmnopqrstuvwxyzva", t = "abcdefghijklmnopqrstuvwxyzck"
            #  *  Output: false
            #  */
            logging.info("Input: s = \"%s\", t = \"%s\"", s, t)

            retVal = pSolution.isIsomorphic(s, t)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
