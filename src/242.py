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
    def isAnagram(self, s: str, t: str) -> bool:
        retVal = True

        sSize = len(s)
        tSzie = len(t)
        if sSize != tSzie:
            retVal = False
            return retVal

        letterSize = 26  # s and t consist of lowercase English letters.
        letterCount = [0] * letterSize
        for cS, cT in zip(s, t):
            letterCount[ord(cS) - ord('a')] += 1
            letterCount[ord(cT) - ord('a')] -= 1

        for i in range(letterSize):
            if letterCount[i] != 0:
                retVal = False
                break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print("")

        pSolution = Solution()
        for s, t in zip(["anagram", "rat"], ["nagaram", "car"]):
            # /* Example
            #  *  Input: s = "anagram", t = "nagaram"
            #  *  Output: true
            #  *
            #  *  Input: s = "rat", t = "car"
            #  *  Output: false
            #  */
            logging.info("Input: s = \"%s\", t = \"%s\"", s, t)

            retVal = pSolution.isAnagram(s, t)
            logging.info("Output: %s", retVal)

            print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass

    sys.exit(0)
