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
    def minMovesToSeat(self, seats: List[int], students: List[int]) -> int:
        retVal = 0

        seats.sort()
        students.sort()
        for x, y in zip(seats, students):
            retVal += abs(x-y)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for seats, students in zip([[3, 1, 5], [4, 1, 5, 9], [2, 2, 6, 6]], [[2, 7, 4], [1, 3, 2, 6], [1, 3, 2, 6]]):
            # /* Example
            #  *  Input: seats = [3,1,5], students = [2,7,4]
            #  *  Output: 4
            #  *
            #  *  Input: seats = [4,1,5,9], students = [1,3,2,6]
            #  *  Output: 7
            #  *
            #  *  Input: seats = [2,2,6,6], students = [1,3,2,6]
            #  *  Output: 4
            #  */
            logging.info("Input: seats = %s, students = %s", seats, students)

            retVal = pSolution.minMovesToSeat(seats, students)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
