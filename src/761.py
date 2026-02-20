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
    def makeLargestSpecial(self, s: str) -> str:
        retVal = ""

        sSize = len(s)
        if sSize <= 2:
            retVal = s
            return retVal

        cnt = 0
        left = 0
        subs = list()
        for i, ch in enumerate(s):
            if ch == "1":
                cnt += 1
                continue
            cnt -= 1
            if cnt == 0:
                subs.append("1" + self.makeLargestSpecial(s[left+1:i]) + "0")
                left = i + 1
        subs.sort(reverse=True)
        retVal = "".join(subs)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["11011000", "10"]:
            # /* Example
            #  *  Input: s = "11011000"
            #  *  Output: "11100100"
            #  *
            #  *  Input: s = "10"
            #  *  Output: "10"
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.makeLargestSpecial(s)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
