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
    def reverseVowels(self, s: str) -> str:
        retVal = ""

        s = list(s)
        sSize = len(s)

        left = 0
        right = sSize - 1
        while left < right:
            while (left < sSize) and (s[left] not in "aeiouAEIOU"):
                left += 1
            while (right > 0) and (s[right] not in "aeiouAEIOU"):
                right -= 1

            if left < right:
                s[left], s[right] = s[right], s[left]
                left += 1
                right -= 1
        retVal = "".join(s)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["hello", "leetcode", ".,"]:
            # /* Example
            #  *  Input: s = "hello"
            #  *  Output: "holle"
            #  *
            #  *  Input: s = "leetcode"
            #  *  Output: "leotcede"
            #  *
            #  *  Input: s = ".,"
            #  *  Output: ".,"
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.reverseVowels(s)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
