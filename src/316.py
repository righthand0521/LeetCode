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
    def removeDuplicateLetters(self, s: str) -> str:
        retVal = None

        stack = []
        visit = set()
        appears = Counter(s)
        for c in s:
            if c not in visit:
                while stack and c < stack[-1] and appears[stack[-1]] > 0:
                    visit.discard(stack.pop())
                visit.add(c)
                stack.append(c)
            appears[c] -= 1
        retVal = ''.join(stack)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["bcabc", "cbacdcbc"]:
            # /* Example
            #  *  Input: s = "bcabc"
            #  *  Output: "abc"
            #  *
            #  *  Input: s = "cbacdcbc"
            #  *  Output: "acdb"
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.removeDuplicateLetters(s)
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
