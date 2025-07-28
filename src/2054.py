import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from typing import List, Optional


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
    def maxTwoEvents(self, events: List[List[int]]) -> int:
        retVal = 0

        times = []
        for event in events:
            times.append([event[0], 1, event[2]])  # 1 denotes start time.
            times.append([event[1] + 1, 0, event[2]])  # 0 denotes end time.
        times.sort()

        maxValue = 0
        for timeValue in times:
            # If current time is a start time, find maximum sum of maximum end time till now.
            if timeValue[1]:
                retVal = max(retVal, timeValue[2] + maxValue)
            else:
                maxValue = max(maxValue, timeValue[2])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for events in [
            [[1, 3, 2], [4, 5, 2], [2, 4, 3]],
            [[1, 3, 2], [4, 5, 2], [1, 5, 5]],
            [[1, 5, 3], [1, 5, 1], [6, 6, 5]]
        ]:
            # /* Example
            #  *  Input: events = [[1,3,2],[4,5,2],[2,4,3]]
            #  *  Output: 4
            #  *
            #  *  Input: events = [[1,3,2],[4,5,2],[1,5,5]]
            #  *  Output: 5
            #  *
            #  *  Input: events = [[1,5,3],[1,5,1],[6,6,5]]
            #  *  Output: 8
            #  */
            logging.info("Input: events = %s", events)

            retVal = pSolution.maxTwoEvents(events)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
