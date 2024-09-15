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
    def findTheLongestSubstring(self, s: str) -> int:
        retVal = 0

        characterMap = [0] * 26  # s contains only lowercase English letters.
        characterMap[ord("a") - ord("a")] = 1
        characterMap[ord("e") - ord("a")] = 2
        characterMap[ord("i") - ord("a")] = 4
        characterMap[ord("o") - ord("a")] = 8
        characterMap[ord("u") - ord("a")] = 16
        mp = [-1] * 32  # 1+2+4+8+16=31 < 32

        sSize = len(s)
        prefixXOR = 0
        for i in range(sSize):
            prefixXOR ^= characterMap[ord(s[i]) - ord("a")]
            if (mp[prefixXOR] == -1) and (prefixXOR != 0):
                mp[prefixXOR] = i
            retVal = max(retVal, i - mp[prefixXOR])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["eleetminicoworoep", "leetcodeisgreat", "bcbcbc"]:
            # /* Example
            #  *  Input: s = "eleetminicoworoep"
            #  *  Output: 13
            #  *
            #  *  Input: s = "leetcodeisgreat"
            #  *  Output: 5
            #  *
            #  *  Input: s = "bcbcbc"
            #  *  Output: 6
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.findTheLongestSubstring(s)
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
