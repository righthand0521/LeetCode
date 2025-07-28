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
    def backtracking(self, k: int, n: int, start: int, combine: List[int], answer: List[List[int]]) -> None:
        if (len(combine) > k) or (n < 0):
            return

        if (len(combine) == k) and (n == 0):
            answer.append(combine[:])
            return

        # Only numbers 1 through 9 are used.
        for i in range(start, 10):
            combine.append(i)
            self.backtracking(k, n-i, i+1, combine, answer)
            combine.pop()

    def combinationSum3(self, k: int, n: int) -> List[List[int]]:
        retVal = []

        combine = []
        self.backtracking(k, n, 1, combine, retVal)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for k, n in zip([3, 3, 4, 2], [7, 9, 1, 18]):
            # /* Example
            #  *  Input: k = 3, n = 7
            #  *  Output: [[1,2,4]]
            #  *
            #  *  Input: k = 3, n = 9
            #  *  Output: [[1,2,6],[1,3,5],[2,3,4]]
            #  *
            #  *  Input: k = 4, n = 1
            #  *  Output: []
            #  *
            #  *  Input: k = 2, n = 18
            #  *  Output: []
            #  */
            logging.info("Input: k = %s, n = %s", k, n)

            retVal = pSolution.combinationSum3(k, n)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
