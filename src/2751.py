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
    def survivedRobotsHealths(self, positions: List[int], healths: List[int], directions: str) -> List[int]:
        retVal = []

        positionsSize = len(positions)

        # Sort indices based on their positions
        indices = list(range(positionsSize))
        indices.sort(key=lambda x: positions[x])

        stack = deque()
        for currentIndex in indices:
            if directions[currentIndex] == "R":
                stack.append(currentIndex)
                continue

            while stack and healths[currentIndex] > 0:
                # Pop the top robot from the stack for collision check
                topIndex = stack.pop()

                if healths[topIndex] > healths[currentIndex]:
                    # Top robot survives, current robot is destroyed
                    healths[topIndex] -= 1
                    healths[currentIndex] = 0
                    stack.append(topIndex)
                elif healths[topIndex] < healths[currentIndex]:
                    # Current robot survives, top robot is destroyed
                    healths[currentIndex] -= 1
                    healths[topIndex] = 0
                else:
                    # Both robots are destroyed
                    healths[currentIndex] = 0
                    healths[topIndex] = 0

        # Collect surviving robots
        for index in range(positionsSize):
            if healths[index] > 0:
                retVal.append(healths[index])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for positions, healths, directions in zip([[5, 4, 3, 2, 1], [3, 5, 2, 6], [1, 2, 5, 6]],
                                                  [[2, 17, 9, 15, 10], [
                                                      10, 10, 15, 12], [10, 10, 11, 11]],
                                                  ["RRRRR", "RLRL", "RLRL"]):
            # /* Example
            #  *  Input: positions = [5,4,3,2,1], healths = [2,17,9,15,10], directions = "RRRRR"
            #  *  Output: [2,17,9,15,10]
            #  *
            #  *  Input: positions = [3,5,2,6], healths = [10,10,15,12], directions = "RLRL"
            #  *  Output: [14]
            #  *
            #  *  Input: positions = [1,2,5,6], healths = [10,10,11,11], directions = "RLRL"
            #  *  Output: []
            #  */
            logging.info("Input: positions = %s, healths = %s, directions = \"%s\"", positions, healths, directions)

            retVal = pSolution.survivedRobotsHealths(positions, healths, directions)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
