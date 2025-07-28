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
    def __init__(self):
        self.answer = 0
        self.n = 0
        self.requests = [[]]
        self.requestsSize = 0

    def backtracking(self, index: int, building: List[int], count: int, zero: int) -> None:
        if index == self.requestsSize:
            if zero == self.n:
                self.answer = max(self.answer, count)
            return

        self.backtracking(index + 1, building, count, zero)

        z = zero
        count += 1
        x, y = self.requests[index]
        zero -= (building[x] == 0)
        building[x] -= 1
        zero += (building[x] == 0)
        zero -= (building[y] == 0)
        building[y] += 1
        zero += building[y] == 0
        self.backtracking(index + 1, building, count, zero)
        building[y] -= 1
        building[x] += 1
        count -= 1
        zero = z

    def maximumRequests(self, n: int, requests: List[List[int]]) -> int:
        retVal = 0

        self.answer = 0
        self.n = n
        self.requests = requests
        self.requestsSize = len(requests)

        building = [0] * n
        count = 0
        zero = n
        self.backtracking(0, building, count, zero)
        retVal = self.answer

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, requests in zip([5, 3, 4],
                               [[[0, 1], [1, 0], [0, 1], [1, 2], [2, 0], [3, 4]],
                                [[0, 0], [1, 2], [2, 1]],
                                [[0, 3], [3, 1], [1, 2], [2, 0]]]):
            # /* Example
            #  *  Input: n = 5, requests = [[0,1],[1,0],[0,1],[1,2],[2,0],[3,4]]
            #  *  Output: 5
            #  *
            #  *  Input: n = 3, requests = [[0,0],[1,2],[2,1]]
            #  *  Output: 3
            #  *
            #  *  Input: n = 4, requests = [[0,3],[3,1],[1,2],[2,0]]
            #  *  Output: 4
            #  */
            logging.info("Input: n = %s, requests = %s", n, requests)

            retVal = pSolution.maximumRequests(n, requests)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
