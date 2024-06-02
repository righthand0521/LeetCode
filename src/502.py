import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from typing import List, Optional

from tree import TreeNode


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
    def findMaximizedCapital(self, k: int, w: int, profits: List[int], capital: List[int]) -> int:
        retVal = 0

        # https://leetcode.com/problems/ipo/solutions/3219987/day-54-c-priority-queue-easiest-beginner-friendly-sol
        profitsSize = len(profits)
        projects = [(capital[i], profits[i]) for i in range(profitsSize)]
        projects.sort()

        i = 0
        maximizeCapital = []
        while k > 0:
            while (i < profitsSize) and (projects[i][0] <= w):
                heappush(maximizeCapital, -projects[i][1])
                i += 1
            if not maximizeCapital:
                break
            w -= heappop(maximizeCapital)
            k -= 1
        retVal = w

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for k, w, profits, capital in zip([2, 3], [0, 0], [[1, 2, 3], [1, 2, 3]], [[0, 1, 1], [0, 1, 2]]):
            # /* Example
            #  *  Input: k = 2, w = 0, profits = [1,2,3], capital = [0,1,1]
            #  *  Output: 4
            #  *
            #  *  Input: k = 3, w = 0, profits = [1,2,3], capital = [0,1,2]
            #  *  Output: 6
            #  */
            logging.info(
                "Input: k = %s, w = %s, profits = %s, capital = %s", k, w, profits, capital)

            retVal = pSolution.findMaximizedCapital(k, w, profits, capital)
            logging.info("Output: %s", retVal)

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
