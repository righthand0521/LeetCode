﻿import sys
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
    def numRescueBoats(self, people: List[int], limit: int) -> int:
        retVal = 0

        people.sort()
        left = 0
        right = len(people) - 1
        while left <= right:
            if people[left] + people[right] <= limit:
                left += 1
            right -= 1
            retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for people, limit in zip([[1, 2], [3, 2, 2, 1], [3, 5, 3, 4]], [3, 3, 5]):
            # /* Example
            #  *  Input: people = [1,2], limit = 3
            #  *  Output: 1
            #  *
            #  *  Input: people = [3,2,2,1], limit = 3
            #  *  Output: 3
            #  *
            #  *  Input: people = [3,5,3,4], limit = 5
            #  *  Output: 4
            #  */
            logging.info("Input: people = %s, limit = %d", people, limit)

            retVal = pSolution.numRescueBoats(people, limit)
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
