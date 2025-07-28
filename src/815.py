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
    def numBusesToDestination(self, routes: List[List[int]], source: int, target: int) -> int:
        retVal = -1

        stations = defaultdict(set)
        for i, stops in enumerate(routes):
            for stop in stops:
                stations[stop].add(i)

        routes = [set(x) for x in routes]

        buses = set()
        stops = {source}
        q = deque([(source, 0)])
        while q:
            pos, cost = q.popleft()
            if pos == target:
                retVal = cost
                break

            for bus in stations[pos] - buses:
                for stop in routes[bus] - stops:
                    buses.add(bus)
                    stops.add(stop)
                    q.append((stop, cost + 1))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for routes, source, target in [
            [[[1, 2, 7], [3, 6, 7]], 1, 6],
            [[[7, 12], [4, 5, 15], [6], [15, 19], [9, 12, 13]], 15, 12]
        ]:
            # /* Example
            #  *  Input: routes = [[1,2,7],[3,6,7]], source = 1, target = 6
            #  *  Output: 2
            #  *
            #  *  Input: routes = [[7,12],[4,5,15],[6],[15,19],[9,12,13]], source = 15, target = 12
            #  *  Output: -1
            #  */
            logging.info("Input: routes = %s, source = %s, target = %s", routes, source, target)

            retVal = pSolution.numBusesToDestination(routes, source, target)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
