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
    def timeRequiredToBuy(self, tickets: List[int], k: int) -> int:
        retVal = 0

        ticketsSize = len(tickets)
        for i in range(ticketsSize):
            if i <= k:
                retVal += min(tickets[i], tickets[k])
            else:
                retVal += min(tickets[i], (tickets[k]-1))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for tickets, k in zip([[2, 3, 2], [5, 1, 1, 1]], [2, 0]):
            # /* Example
            #  *  Input: tickets = [2,3,2], k = 2
            #  *  Output: 6
            #  *
            #  *  Input: tickets = [5,1,1,1], k = 0
            #  *  Output: 8
            #  */
            logging.info("Input: tickets = %s, k = %s", tickets, k)

            retVal = pSolution.timeRequiredToBuy(tickets, k)
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
