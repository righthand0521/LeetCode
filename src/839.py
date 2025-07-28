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
    def find(self, f: List[int], x: int) -> int:
        retVal = x

        if f[x] == x:
            return retVal

        f[x] = self.find(f, f[x])
        retVal = f[x]

        return retVal

    def check(self, a: str, b: str) -> bool:
        retVal = False

        num = 0
        for ac, bc in zip(a, b):
            if ac == bc:
                continue

            num += 1
            if num > 2:
                return retVal

        retVal = True

        return retVal

    def numSimilarGroups(self, strs: List[str]) -> int:
        retVal = 0

        strsSize = len(strs)
        f = list(range(strsSize))

        for i in range(strsSize):
            for j in range(i + 1, strsSize):
                fi = self.find(f, i)
                fj = self.find(f, j)
                if fi == fj:
                    continue

                if self.check(strs[i], strs[j]):
                    f[fi] = fj

        retVal = sum(1 for i in range(strsSize) if f[i] == i)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for strs in [["tars", "rats", "arts", "star"], ["omv", "ovm"]]:
            # /* Example
            #  *  Input: strs = ["tars","rats","arts","star"]
            #  *  Output: 2
            #  *
            #  *  Input: strs = ["omv","ovm"]
            #  *  Output: 1
            #  */
            logging.info("Input: strs = %s", strs)

            retVal = pSolution.numSimilarGroups(strs)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
