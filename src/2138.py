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
    def divideString(self, s: str, k: int, fill: str) -> List[str]:
        retVal = []

        sSize = len(s)
        for i in range(0, sSize, k):
            part = s[i:i + k]
            partSize = len(part)
            if partSize < k:
                part += (fill * (k - partSize))
            retVal.append(part)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, k, fill in [("abcdefghi", 3, 'x'), ("abcdefghij", 3, 'x')]:
            # /* Example
            #  *  Input: s = "abcdefghi", k = 3, fill = "x"
            #  *  Output: ["abc","def","ghi"]
            #  *
            #  *  Input: s = "abcdefghij", k = 3, fill = "x"
            #  *  Output: ["abc","def","ghi","jxx"]
            #  */
            logging.info("Input: s = \"%s\", k = %s, fill = \"%s\"\n", s, k, fill)

            retVal = pSolution.divideString(s, k, fill)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
