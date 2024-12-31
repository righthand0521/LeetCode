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
    def mincostTickets(self, days: List[int], costs: List[int]) -> int:
        retVal = 0

        dp = [0 for _ in range(days[-1] + 1)]
        idx = 0
        for i in range(1, len(dp)):
            if i != days[idx]:
                dp[i] = dp[i-1]
                continue
            dp[i] = min(dp[max(0, i - 1)] + costs[0], dp[max(0, i - 7)] + costs[1], dp[max(0, i - 30)] + costs[2])
            idx += 1
        retVal = dp[-1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for days, costs in zip([[1, 4, 6, 7, 8, 20], [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 30, 31], [1, 4, 6, 7, 8, 20]],
                               [[2, 7, 15], [2, 7, 15], [7, 2, 15]]):
            # /* Example
            #  *  Input: days = [1,4,6,7,8,20], costs = [2,7,15]
            #  *  Output: 11
            #  *
            #  *  Input: days = [1,2,3,4,5,6,7,8,9,10,30,31], costs = [2,7,15]
            #  *  Output: 17
            #  *
            #  *  Input: days = [1,4,6,7,8,20], costs = [7,2,15]
            #  *  Output: 6
            #  */
            logging.info("Input: days = %s, costs = %s", days, costs)

            retVal = pSolution.mincostTickets(days, costs)
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
