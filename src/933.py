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


class RecentCounter:
    def __init__(self):
        self.requests = []
        heapify(self.requests)

    def ping(self, t: int) -> int:
        retVal = 0

        heappush(self.requests, t)
        for _ in range(len(self.requests)):
            if self.requests[0] < (t-3000):
                heappop(self.requests)
        retVal = len(self.requests)

        return retVal

# Your RecentCounter object will be instantiated and called as such:
# obj = RecentCounter()
# param_1 = obj.ping(t)


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, num in zip([["RecentCounter", "ping", "ping", "ping", "ping"]], [[None, 1, 100, 3001, 3002]]):
            # /* Example
            #  *  Input
            #  *  ["RecentCounter", "ping", "ping", "ping", "ping"]
            #  *  [[], [1], [100], [3001], [3002]]
            #  *  Output
            #  *  [null, 1, 2, 3, 3]
            #  */
            logging.info("%s", methods)
            displayStr = []
            for p in num:
                if p == None:
                    displayStr.append([])
                else:
                    displayStr.append([p])
            logging.info("%s", displayStr)

            displayStr = []
            obj = RecentCounter()
            for p, q in zip(methods, num):
                if p == "RecentCounter":
                    displayStr.append(None)
                elif p == "ping":
                    retVal = obj.ping(q)
                    displayStr.append(retVal)
            logging.info("Output")
            logging.info("%s", displayStr)

            print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
