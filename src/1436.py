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
    def destCity(self, paths: List[List[str]]) -> str:
        retVal = ""

        outgoing = set()
        for cityA, cityB in paths:
            outgoing.add(cityA)

        for cityA, cityB in paths:
            if cityB not in outgoing:
                retVal = cityB
                break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for paths in [[["London", "New York"], ["New York", "Lima"], ["Lima", "Sao Paulo"]],
                      [["B", "C"], ["D", "B"], ["C", "A"]],
                      [["A", "Z"]]]:
            # /* Example
            #  *  Input: paths = [["London","New York"],["New York","Lima"],["Lima","Sao Paulo"]]
            #  *  Output: "Sao Paulo"
            #  *
            #  *  Input: paths = [["B","C"],["D","B"],["C","A"]]
            #  *  Output: "A"
            #  *
            #  *  Input: paths = [["A","Z"]]
            #  *  Output: "Z"
            #  */
            logging.info("Input: paths = %s", paths)

            retVal = pSolution.destCity(paths)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
