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

        # cuts[i] is True : we don't need to check col[i] <= col[i+1]
        cuts = [False] * (strsSize - 1)

        for j in range(strSize):
            needDelete = False

            # Evaluate whether we can keep this column
            for i in range(strsSize - 1):
                if (cuts[i] == False) and (strs[i][j] > strs[i + 1][j]):
                    # Can't keep the column - delete and continue
                    retVal += 1
                    needDelete = True
                    break
            if needDelete == True:
                continue

            # Update 'cuts' information
            for i in range(strsSize - 1):
                if strs[i][j] < strs[i + 1][j]:
                    cuts[i] = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for strs in [["ca", "bb", "ac"], ["xc", "yb", "za"], ["zyx", "wvu", "tsr"]]:
            # /* Example
            #  *  Input: strs = ["ca","bb","ac"]
            #  *  Output: 1
            #  *
            #  *  Input: strs = ["xc","yb","za"]
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
