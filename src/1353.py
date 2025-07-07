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
    def maxEvents(self, events: List[List[int]]) -> int:
        retVal = 0

        events.sort(reverse=1)

        minHeap = []
        startDay = 0
        while events or minHeap:
            if not minHeap:
                startDay = events[-1][0]

            while events and events[-1][0] <= startDay:
                heappush(minHeap, events.pop()[1])

            heappop(minHeap)
            retVal += 1
            startDay += 1
            while minHeap and minHeap[0] < startDay:
                heappop(minHeap)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for events in [[[1, 2], [2, 3], [3, 4]], [[1, 2], [2, 3], [3, 4], [1, 2]]]:
            # /* Example
            #  *  Input: events = [[1,2],[2,3],[3,4]]
            #  *  Output: 3
            #  *
            #  *  Input: events= [[1,2],[2,3],[3,4],[1,2]]
            #  *  Output: 4
            #  */
            logging.info("Input: events = %s", events)

            retVal = pSolution.maxEvents(events)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
