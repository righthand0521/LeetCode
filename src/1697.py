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
        retVal = 0

        if f[x] != x:
            f[x] = self.find(f, f[x])
        retVal = f[x]

        return retVal

    def merge(self, f: List[int], src: int, dst: int) -> None:
        f[self.find(f, src)] = self.find(f, dst)

    def distanceLimitedPathsExist(self, n: int, edgeList: List[List[int]], queries: List[List[int]]) -> List[bool]:
        retVal = []

        retVal = [False] * len(queries)
        k = 0
        edgeList.sort(key=lambda e: e[2])
        f = list(range(n))
        for i, (p, q, limit) in sorted(enumerate(queries), key=lambda p: p[1][2]):
            while k < len(edgeList) and edgeList[k][2] < limit:
                self.merge(f, edgeList[k][0], edgeList[k][1])
                k += 1

            if self.find(f, p) == self.find(f, q):
                retVal[i] = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, edgeList, queries in zip([3, 5],
                                        [[[0, 1, 2], [1, 2, 4], [2, 0, 8], [1, 0, 16]],
                                         [[0, 1, 10], [1, 2, 5], [2, 3, 9], [3, 4, 13]]],
                                        [[[0, 1, 2], [0, 2, 5]], [[0, 4, 14], [1, 4, 13]]]):
            # /* Example
            #  *  Input: n = 3, edgeList = [[0,1,2],[1,2,4],[2,0,8],[1,0,16]], queries = [[0,1,2],[0,2,5]]
            #  *  Output: [false,true]
            #  *
            #  *  Input: n = 5, edgeList = [[0,1,10],[1,2,5],[2,3,9],[3,4,13]], queries = [[0,4,14],[1,4,13]]
            #  *  Output: [true,false]
            #  */
            logging.info(
                "Input: n = %s, edgeList = %s, queries = %s", n, edgeList, queries)

            retVal = pSolution.distanceLimitedPathsExist(n, edgeList, queries)
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
