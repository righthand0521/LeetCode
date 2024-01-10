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
    def nearestExit(self, maze: List[List[str]], entrance: List[int]) -> int:
        retVal = -1

        mazeSize = len(maze)
        mazeColSize = len(maze[0])
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]

        bfsQueue = deque()
        bfsQueue.append((entrance[0], entrance[1], 0))
        maze[entrance[0]][entrance[1]] = '+'
        while bfsQueue:
            x, y, steps = bfsQueue.popleft()
            for diffX, diffY in directions:
                nextX = x + diffX
                nextY = y + diffY
                if (nextX < 0) or (nextX >= mazeSize):
                    continue
                elif (nextY < 0) or (nextY >= mazeColSize):
                    continue
                elif maze[nextX][nextY] == '+':
                    continue

                if (nextX == 0) or (nextX == mazeSize - 1) or (nextY == 0) or (nextY == mazeColSize - 1):
                    retVal = steps + 1
                    return retVal
                maze[nextX][nextY] = '+'
                bfsQueue.append((nextX, nextY, steps + 1))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for maze, entrance in zip([[["+", "+", ".", "+"], [".", ".", ".", "+"], ["+", "+", "+", "."]],
                                   [["+", "+", "+"], [".", ".", "."],
                                       ["+", "+", "+"]],
                                   [[".", "+"]]],
                                  [[1, 2],
                                   [1, 0],
                                   [0, 0]]):
            # /* Example
            #  *  Input: maze = [["+","+",".","+"],[".",".",".","+"],["+","+","+","."]], entrance = [1,2]
            #  *  Output: 1
            #  *
            #  *  Input: maze = [["+","+","+"],[".",".","."],["+","+","+"]], entrance = [1,0]
            #  *  Output: 2
            #  *
            #  *  Input: maze = [[".","+"]], entrance = [0,0]
            #  *  Output: -1
            #  */
            logging.info("Input: maze = %s, entrance = %s", maze, entrance)

            retVal = pSolution.nearestExit(maze, entrance)
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
