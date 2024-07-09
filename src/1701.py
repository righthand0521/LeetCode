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
    def averageWaitingTime(self, customers: List[List[int]]) -> float:
        retVal = 0

        nextIdleTime = 0
        netWaitTime = 0
        for customer in customers:
            nextIdleTime = max(customer[0], nextIdleTime) + customer[1]
            netWaitTime += (nextIdleTime - customer[0])

        customersSize = len(customers)
        retVal = netWaitTime / customersSize

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for customers in [[[1, 2], [2, 5], [4, 3]], [[5, 2], [5, 4], [10, 3], [20, 1]]]:
            # /* Example
            #  *  Input: customers = [[1,2],[2,5],[4,3]]
            #  *  Output: 5.00000
            #  *
            #  *  Input: customers = [[5,2],[5,4],[10,3],[20,1]]
            #  *  Output: 3.25000
            #  */
            logging.info("Input: customers = %s", customers)

            retVal = pSolution.averageWaitingTime(customers)
            logging.info("Output: %.5f", retVal)

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
