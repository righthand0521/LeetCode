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
    def minimumTotalDistance(self, robot: List[int], factory: List[List[int]]) -> int:
        retVal = 0

        # Sort robots and factories by position
        robot.sort()
        factory.sort(key=lambda x: x[0])

        # Flatten factory positions according to their capacities
        factoryPositions = []
        for f in factory:
            for _ in range(f[1]):
                factoryPositions.append(f[0])

        robotSize = len(robot)
        factoryPositionsSize = len(factoryPositions)
        dp = [[0] * (factoryPositionsSize + 1) for _ in range(robotSize + 1)]

        # Initialize base cases
        for i in range(robotSize):
            dp[i][factoryPositionsSize] = 1e12  # No factories left

        # Fill DP table bottom-up
        for i in range(robotSize - 1, -1, -1):
            for j in range(factoryPositionsSize - 1, -1, -1):
                # Option 1: Assign current robot to current factory
                assign = abs(robot[i] - factoryPositions[j]) + dp[i + 1][j + 1]

                # Option 2: Skip current factory for the current robot
                skip = dp[i][j + 1]

                dp[i][j] = min(assign, skip)  # Take the minimum option

        # Minimum distance starting from first robot and factory
        retVal = dp[0][0]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for robot, factory in zip([[0, 4, 6], [1, -1]], [[[2, 2], [6, 2]], [[-2, 1], [2, 1]]]):
            # /* Example
            #  *  Input: robot = [0,4,6], factory = [[2,2],[6,2]]
            #  *  Output: 4
            #  *
            #  *  Input: robot = [1,-1], factory = [[-2,1],[2,1]]
            #  *  Output: 2
            #  */
            logging.info("Input: robot = %s, factory = %s", robot, factory)

            retVal = pSolution.minimumTotalDistance(robot, factory)
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
