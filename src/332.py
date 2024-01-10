import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop
from copy import deepcopy


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
    def dfs(self, departs: str, flight: defaultdict, retVal: List[str]) -> None:
        while flight[departs]:
            tmp = heappop(flight[departs])
            self.dfs(tmp, flight, retVal)
        retVal.append(departs)

    def findItinerary(self, tickets: List[List[str]]) -> List[str]:
        retVal = []

        flight = defaultdict(list)
        for departure, arrival in tickets:
            flight[departure].append(arrival)
        for key in flight:
            heapify(flight[key])

        self.dfs("JFK", flight, retVal)
        retVal = retVal[::-1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for tickets in [[["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]],
                        [["JFK", "SFO"], ["JFK", "ATL"], ["SFO", "ATL"], ["ATL", "JFK"], ["ATL", "SFO"]]]:
            # /* Example
            #  *  Input: tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
            #  *  Output: ["JFK","MUC","LHR","SFO","SJC"]
            #  *
            #  *  Input: tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
            #  *  Output: ["JFK","ATL","JFK","SFO","ATL","SFO"]
            #  */
            logging.info(
                "Input: tickets = %s", tickets)

            retVal = pSolution.findItinerary(tickets)
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
