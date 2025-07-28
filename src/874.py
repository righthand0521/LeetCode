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
    def __init__(self) -> None:
        self.directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

    def hashCoordinates(self, x: int, y: int) -> int:
        retVal = 0

        HASH_MULTIPLIER = 60001  # Slightly larger than 2 * max coordinate value
        retVal = x + HASH_MULTIPLIER * y

        return retVal

    def robotSim(self, commands: List[int], obstacles: List[List[int]]) -> int:
        retVal = 0

        obstacleSet = {self.hashCoordinates(x, y) for x, y in obstacles}

        x = 0
        y = 0
        maxDistanceSquared = 0
        currentDirection = 0
        for command in commands:
            if command == -1:
                currentDirection = (currentDirection + 1) % 4
                continue
            elif command == -2:
                currentDirection = (currentDirection + 3) % 4
                continue

            dx, dy = self.directions[currentDirection]
            for _ in range(command):
                nextX = x + dx
                nextY = y + dy
                if self.hashCoordinates(nextX, nextY) in obstacleSet:
                    break
                x = nextX
                y = nextY

            maxDistanceSquared = max(maxDistanceSquared, x * x + y * y)

        retVal = maxDistanceSquared

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for commands, obstacles in zip([[4, -1, 3], [4, -1, 4, -2, 4], [6, -1, -1, 6]], [[], [[2, 4]], []]):
            # /* Example
            #  *  Input: commands = [4,-1,3], obstacles = []
            #  *  Output: 25
            #  *
            #  *  Input: commands = [4,-1,4,-2,4], obstacles = [[2,4]]
            #  *  Output: 65
            #  *
            #  *  Input: commands = [6,-1,-1,6], obstacles = []
            #  *  Output: 36
            #  */
            logging.info("Input: commands = %s, obstacles = %s", commands, obstacles)

            retVal = pSolution.robotSim(commands, obstacles)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
