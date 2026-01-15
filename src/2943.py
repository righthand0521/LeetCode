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
    def maximizeSquareHoleArea(self, n: int, m: int, hBars: List[int], vBars: List[int]) -> int:
        retVal = 0

        hBars.sort()
        hBarsSize = len(hBars)
        hmax = 1
        hcur = 1
        for i in range(1, hBarsSize):
            if hBars[i] == hBars[i - 1] + 1:
                hcur += 1
            else:
                hcur = 1
            hmax = max(hmax, hcur)

        vBars.sort()
        vBarsSize = len(vBars)
        vmax = 1
        vcur = 1
        for i in range(1, vBarsSize):
            if vBars[i] == vBars[i - 1] + 1:
                vcur += 1
            else:
                vcur = 1
            vmax = max(vmax, vcur)

        side = min(hmax, vmax) + 1
        retVal = side * side

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, m, hBars, vBars in [[2, 1, [2, 3], [2]], [1, 1, [2], [2]], [2, 3, [2, 3], [2, 4]]]:
            # /* Example
            #  *  Input: n = 2, m = 1, hBars = [2,3], vBars = [2]
            #  *  Output: 4
            #  *
            #  *  Input: n = 1, m = 1, hBars = [2], vBars = [2]
            #  *  Output: 4
            #  *
            #  *  Input: n = 2, m = 3, hBars = [2,3], vBars = [2,4]
            #  *  Output: 4
            #  */
            logging.info("Input: n = %s, m = %s, hBars = %s, vBars = %s", n, m, hBars, vBars)

            retVal = pSolution.maximizeSquareHoleArea(n, m, hBars, vBars)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
