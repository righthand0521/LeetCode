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
    def asteroidsDestroyed(self, mass: int, asteroids: List[int]) -> bool:
        retVal = True

        asteroids.sort()
        sum = mass
        for asteroid in asteroids:
            if sum < asteroid:
                retVal = False
                break
            sum += asteroid

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for mass, asteroids in zip([10, 5], [[3, 9, 19, 5, 21], [4, 9, 23, 4]]):
            # /* Example
            #  *  Input: mass = 10, asteroids = [3,9,19,5,21]
            #  *  Output: true
            #  *
            #  *  Input: mass = 5, asteroids = [4,9,23,4]
            #  *  Output: false
            #  */
            logging.info("Input: mass = %s, asteroids = %s", mass, asteroids)

            retVal = pSolution.asteroidsDestroyed(mass, asteroids)
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
