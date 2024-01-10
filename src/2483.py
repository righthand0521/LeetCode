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
    def bestClosingTime(self, customers: str) -> int:
        retVal = 0

        # /* At any index, the penalty is the sum of prefix count of 'N' and suffix count of 'Y'.
        #  *  Y Y N Y     N N N N N     Y Y Y Y
        #  *  3 2 1 1 0   0 0 0 0 0 0   4 3 2 1 0
        #  *  0 0 0 1 1   0 1 2 3 4 5   0 0 0 0 0
        #  */
        penalty = customers.count('Y')
        minPenalty = penalty
        customersSize = len(customers)
        for i in range(customersSize):
            if customers[i] == 'Y':
                penalty -= 1
            elif customers[i] == 'N':
                penalty += 1

            if minPenalty > penalty:
                minPenalty = penalty
                retVal = i + 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for customers in ["YYNY", "NNNNN", "YYYY"]:
            # /* Example
            #  *  Input: customers = "YYNY"
            #  *  Output: 2
            #  *
            #  *  Input: customers = "NNNNN"
            #  *  Output: 0
            #  *
            #  *  Input: customers = "YYYY"
            #  *  Output: 4
            #  */
            logging.info("Input: customers = \"%s\"", customers)

            retVal = pSolution.bestClosingTime(customers)
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
