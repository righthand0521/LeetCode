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


# https://leetcode.cn/problems/pyramid-transition-matrix/solutions/3866474/tu-jie-hui-su-vis-you-hua-pythonjavacgo-9kcb9/
class Solution:
    def __init__(self):
        self.groups = None
        self.pyramid = None
        self.vis = None

    def dfs(self, i: int, j: int) -> bool:
        retVal = False

        if i < 0:
            retVal = True
        elif self.pyramid[i] in self.vis:
            retVal = False
        elif j == i + 1:
            self.vis.add(self.pyramid[i])
            retVal = self.dfs(i - 1, 0)
        else:
            for top in self.groups[self.pyramid[i + 1] >> (j * 3) & 7][self.pyramid[i + 1] >> ((j + 1) * 3) & 7]:
                self.pyramid[i] &= ~(7 << (j * 3))
                self.pyramid[i] |= top << (j * 3)
                if self.dfs(i, j + 1):
                    retVal = True
                    break

        return retVal

    def pyramidTransition(self, bottom: str, allowed: List[str]) -> bool:
        retVal = False

        self.groups = [[[] for _ in range(7)] for _ in range(7)]
        for a, b, c in allowed:
            self.groups[ord(a) & 31][ord(b) & 31].append(ord(c) & 31)

        bottomSize = len(bottom)
        self.pyramid = [0] * bottomSize
        for i, ch in enumerate(bottom):
            self.pyramid[-1] |= (ord(ch) & 31) << (i * 3)

        self.vis = set()

        retVal = self.dfs(bottomSize - 2, 0)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for bottom, allowed in [["BCD", ["BCC", "CDE", "CEA", "FFF"]],
                                ["AAAA", ["AAB", "AAC", "BCD", "BBE", "DEF"]]]:
            # /* Example
            #  *  Input: bottom = "BCD", allowed = ["BCC","CDE","CEA","FFF"]
            #  *  Output: true
            #  *
            #  *  Input: bottom = "AAAA", allowed = ["AAB","AAC","BCD","BBE","DEF"]
            #  *  Output: false
            #  */
            logging.info("Input: bottom = \"%s\", allowed = %s", bottom, allowed)

            retVal = pSolution.pyramidTransition(bottom, allowed)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
