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
    def findJudge(self, n: int, trust: List[List[int]]) -> int:
        retVal = -1

        indegree = [0] * n
        outdegree = [0] * n
        for a, b in trust:
            indegree[b-1] += 1
            outdegree[a-1] += 1

        for idx, value in enumerate(outdegree):
            if value != 0:
                continue

            if indegree[idx] == (n-1):
                retVal = idx + 1
                break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, trust in zip([2, 3, 3, 1], [[[1, 2]], [[1, 3], [2, 3]], [[1, 3], [2, 3], [3, 1]], []]):
            # /* Example
            #  *  Input: n = 2, trust = [[1,2]]
            #  *  Output: 2
            #  *
            #  *  Input: n = 3, trust = [[1,3],[2,3]]
            #  *  Output: 3
            #  *
            #  *  Input: n = 3, trust = [[1,3],[2,3],[3,1]]
            #  *  Output: -1
            #  *
            #  *  Input: n = 1, trust = []
            #  *  Output: 1
            #  */
            logging.info("Input: n = %s, trust = %s", n, trust)

            retVal = pSolution.findJudge(n, trust)
            logging.info("Output: %d", retVal)

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
