import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop


def logging_setting():
    LOG_LEVEL = logging.INFO  # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt="%Y/%m/%d %H:%M:%S",
    )


class Solution:
    def eliminateMaximum(self, dist: List[int], speed: List[int]) -> int:
        retVal = 0

        arrival = []
        for d, s in zip(dist, speed):
            arrival.append(d / s)

        arrival.sort()

        for idx, value in enumerate(arrival):
            if value <= idx:
                break
            retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for dist, speed in zip(
            [[1, 3, 4], [1, 1, 2, 3], [3, 2, 4], [4, 2, 3]],
            [[1, 1, 1], [1, 1, 1, 1], [5, 3, 2], [2, 1, 1]],
        ):
            # /* Example
            #  *  Input: dist = [1,3,4], speed = [1,1,1]
            #  *  Output: 3
            #  *
            #  *  Input: dist = [1,1,2,3], speed = [1,1,1,1]
            #  *  Output: 1
            #  *
            #  *  Input: dist = [3,2,4], speed = [5,3,2]
            #  *  Output: 1
            #  *
            #  *  Input: dist = [4,2,3], speed = [2,1,1]
            #  *  Output: 3
            #  */
            logging.info("Input: dist = %s, speed = %s", dist, speed)

            retVal = pSolution.eliminateMaximum(dist, speed)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
