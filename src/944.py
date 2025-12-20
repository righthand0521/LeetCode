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
    def minDeletionSize(self, strs: List[str]) -> int:
        retVal = 0

        strsSize = len(strs)
        strSize = len(strs[0])
        for i in range(strSize):
            for j in range(1, strsSize):
                if strs[j - 1][i] > strs[j][i]:
                    retVal += 1
                    break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for strs in [["cba", "daf", "ghi"], ["a", "b"], ["zyx", "wvu", "tsr"]]:
            # /* Example
            #  *  Input: strs = ["cba","daf","ghi"]
            #  *  Output: 1
            #  *
            #  *  Input: strs = ["a","b"]
            #  *  Output: 0
            #  *
            #  *  Input: strs = ["zyx","wvu","tsr"]
            #  *  Output: 3
            #  */
            logging.info("Input: strs = %s", strs)

            retVal = pSolution.minDeletionSize(strs)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
