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
    def garbageCollection(self, garbage: List[str], travel: List[int]) -> int:
        retVal = 0

        travelSize = len(travel)
        travelPrefixSum = [0] * (travelSize+1)
        for i in range(travelSize):
            travelPrefixSum[i+1] = travelPrefixSum[i] + travel[i]

        # garbage[i] consists only of the characters 'M', 'P' and 'G'
        garbageType = 4

        lastGarbage = [0] * garbageType
        for index, value in enumerate(garbage):
            for p in value:
                if p == 'M':
                    lastGarbage[1] = index
                elif p == 'P':
                    lastGarbage[2] = index
                elif p == 'G':
                    lastGarbage[3] = index

                retVal += 1

        for i in range(garbageType):
            retVal += travelPrefixSum[lastGarbage[i]]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for garbage, travel in zip([["G", "P", "GP", "GG"], ["MMM", "PGM", "GP"]], [[2, 4, 3], [3, 10]]):
            # /* Example
            #  *  Input: garbage = ["G","P","GP","GG"], travel = [2,4,3]
            #  *  Output: 21
            #  *
            #  *  Input: garbage = ["MMM","PGM","GP"], travel = [3,10]
            #  *  Output: 37
            #  */
            logging.info("Input: garbage = %s, travel = %s", garbage, travel)

            retVal = pSolution.garbageCollection(garbage, travel)
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
