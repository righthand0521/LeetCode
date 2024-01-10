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
    def __init__(self) -> None:
        self.method = 1

    def backtracking(self, remain: int, comb: List[int], next: int, n: int, answer: List[List[int]]) -> None:
        if remain == 0:
            answer.append(comb.copy())
            return

        for i in range(next, n+1):
            comb.append(i)
            self.backtracking(remain-1, comb, i+1, n, answer)
            comb.pop()

    def combine(self, n: int, k: int) -> List[List[int]]:
        retVal = []

        if self.method == 1:
            self.backtracking(k, [], 1, n, retVal)
        elif self.method == 2:
            from itertools import combinations
            retVal = list(combinations(range(1, n+1), k))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, k in zip([4, 1], [2, 1]):
            # /* Example
            #  *  Input: n = 4, k = 2
            #  *  Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
            #  *
            #  *  Input: n = 1, k = 1
            #  *  Output: [[1]]
            #  */
            logging.info("Input: n = %s, k = %s", n, k)

            retVal = pSolution.combine(n, k)
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
