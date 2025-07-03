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
    def kthCharacter(self, k: int) -> str:
        retVal = ""

        ans = 0
        while k != 1:
            shift = k.bit_length() - 1
            if (1 << shift) == k:
                shift -= 1
            k -= (1 << shift)
            ans += 1
        retVal = chr(ord("a") + ans)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for k in [5, 10]:
            # /* Example
            #  *  Input: k = 5
            #  *  Output: "b"
            #  *
            #  *  Input: k = 10
            #  *  Output: "c"
            #  */
            logging.info("Input: k = %s", k)

            retVal = pSolution.kthCharacter(k)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
