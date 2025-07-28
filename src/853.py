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
    def carFleet(self, target: int, position: List[int], speed: List[int]) -> int:
        retVal = 0

        # // https://leetcode.com/problems/car-fleet/solutions/139850/c-java-python-straight-forward/
        time = [float(target - p) / s for p, s in sorted(zip(position, speed))]

        current = 0
        for t in time[::-1]:
            if t > current:
                retVal += 1
                current = t

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for target, position, speed in [
            [12, [10, 8, 0, 5, 3], [2, 4, 1, 1, 3]],
            [10, [3], [3]],
            [100, [0, 2, 4], [4, 2, 1]]
        ]:
            # /* Example
            #  *  Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
            #  *  Output: 3
            #  *
            #  *  Input: target = 10, position = [3], speed = [3]
            #  *  Output: 1
            #  *
            #  *  Input: target = 100, position = [0,2,4], speed = [4,2,1]
            #  *  Output: 1
            #  */
            logging.info(
                "Input: target = %s, position = %s, speed = %s", target, position, speed)

            retVal = pSolution.carFleet(target, position, speed)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
