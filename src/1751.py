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
    def dfs(self, events: List[List[int]], eventsSize, k: int, dp, index, count, previousEndDay) -> int:
        retVal = 0

        if (index == eventsSize) or (count == k):
            return retVal

        if events[index][0] <= previousEndDay:
            retVal = self.dfs(events, eventsSize, k, dp,
                              index + 1, count, previousEndDay)
        elif dp[count][index] != -1:
            retVal = dp[count][index]
        else:
            ans1 = self.dfs(events, eventsSize, k, dp,
                            index + 1, count, previousEndDay)
            ans2 = self.dfs(events, eventsSize, k, dp, index + 1,
                            count + 1, events[index][1]) + events[index][2]
            retVal = max(ans1, ans2)
            dp[count][index] = retVal

        return retVal

    def maxValue(self, events: List[List[int]], k: int) -> int:
        retVal = 0

        events.sort()

        eventsSize = len(events)
        dp = [[-1] * eventsSize for _ in range(k + 1)]
        index = 0
        count = 0
        previousEndDay = -1
        retVal = self.dfs(events, eventsSize, k, dp,
                          index, count, previousEndDay)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for events, k in zip([[[1, 2, 4], [3, 4, 3], [2, 3, 1]],
                              [[1, 2, 4], [3, 4, 3], [2, 3, 10]],
                              [[1, 1, 1], [2, 2, 2], [3, 3, 3], [4, 4, 4]]],
                             [2, 2, 3]):
            # /* Example
            #  *  Input: events = [[1,2,4],[3,4,3],[2,3,1]], k = 2
            #  *  Output: 7
            #  *
            #  *  Input: events = [[1,2,4],[3,4,3],[2,3,10]], k = 2
            #  *  Output: 10
            #  *
            #  *  Input: events = [[1,1,1],[2,2,2],[3,3,3],[4,4,4]], k = 3
            #  *  Output: 9
            #  */
            logging.info("Input: events = %s, k = %s", events, k)

            retVal = pSolution.maxValue(events, k)
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
