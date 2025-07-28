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
    # Check if we can place 'm' balls at 'position' with each ball having at least 'x' gap.
    def canPlaceBalls(self, x: int, position: List[int],  m: int) -> bool:
        retVal = False

        positionSize = len(position)

        # Place the first ball at the first position.
        prev_ball_pos = position[0]
        balls_placed = 1

        # Iterate on each 'position' and place a ball there if we can place it.
        for i in range(1, positionSize):

            # Check if we can place the ball at the current position.
            curr_pos = position[i]
            if curr_pos - prev_ball_pos >= x:
                balls_placed += 1
                prev_ball_pos = curr_pos

            # If all 'm' balls are placed, return 'True'.
            if balls_placed == m:
                retVal = True
                break

        return retVal

    def maxDistance(self, position: List[int], m: int) -> int:
        retVal = 0

        position.sort()

        # Initial search space.
        low = 1
        high = int(position[-1] / (m - 1.0)) + 1
        while low <= high:
            middle = low + (high - low) // 2

            # If we can place all balls having a gap at least 'mid',
            if self.canPlaceBalls(middle, position, m):
                retVal = middle    # then 'mid' can be our answer,
                low = middle + 1   # and discard the left half search space.
            else:
                high = middle - 1  # Discard the right half search space.

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for position, m in zip([[1, 2, 3, 4, 7], [5, 4, 3, 2, 1, 1000000000]], [3, 2]):
            # /* Example
            #  *  Input: position = [1,2,3,4,7], m = 3
            #  *  Output: 3
            #  *
            #  *  Input: position = [5,4,3,2,1,1000000000], m = 2
            #  *  Output: 999999999
            #  */
            logging.info("Input: position = %s, m = %s", position, m)

            retVal = pSolution.maxDistance(position, m)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
