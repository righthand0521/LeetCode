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
    def shortestPathAllKeys(self, grid: List[str]) -> int:
        retVal = -1

        #
        gridSize = len(grid)
        gridColSize = len(grid[0])

        #
        startX = 0
        startY = 0
        keyToIdx = dict()
        for i in range(gridSize):
            for j in range(gridColSize):
                if grid[i][j] == "@":
                    startX = i
                    startY = j
                elif grid[i][j].islower():
                    if grid[i][j] not in keyToIdx:
                        idx = len(keyToIdx)
                        keyToIdx[grid[i][j]] = idx

        #
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        bfsQueue = deque([(startX, startY, 0)])
        visited = dict()
        visited[(startX, startY, 0)] = 0
        while bfsQueue:
            x, y, mask = bfsQueue.popleft()

            for diffX, diffY in directions:
                nextX = x + diffX
                nextY = y + diffY

                if (nextX < 0) or (nextX >= gridSize):
                    continue
                elif (nextY < 0) or (nextY >= gridColSize):
                    continue
                elif grid[nextX][nextY] == "#":
                    continue

                if grid[nextX][nextY] == "." or grid[nextX][nextY] == "@":
                    if (nextX, nextY, mask) not in visited:
                        visited[(nextX, nextY, mask)
                                ] = visited[(x, y, mask)] + 1
                        bfsQueue.append((nextX, nextY, mask))
                elif grid[nextX][nextY].islower():
                    idx = keyToIdx[grid[nextX][nextY]]
                    if (nextX, nextY, mask | (1 << idx)) not in visited:
                        visited[(nextX, nextY, mask | (1 << idx))
                                ] = visited[(x, y, mask)] + 1
                        if (mask | (1 << idx)) == (1 << len(keyToIdx)) - 1:
                            retVal = visited[(nextX, nextY, mask | (1 << idx))]
                            return retVal
                        bfsQueue.append((nextX, nextY, mask | (1 << idx)))
                else:
                    idx = keyToIdx[grid[nextX][nextY].lower()]
                    if (mask & (1 << idx)) and (nextX, nextY, mask) not in visited:
                        visited[(nextX, nextY, mask)
                                ] = visited[(x, y, mask)] + 1
                        bfsQueue.append((nextX, nextY, mask))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [["@.a..", "###.#", "b.A.B"], ["@..aA", "..B#.", "....b"], ["@Aa"]]:
            # /* Example
            #  *  Input: grid = ["@.a..","###.#","b.A.B"]
            #  *  Output: 8
            #  *
            #  *  Input: grid = ["@..aA","..B#.","....b"]
            #  *  Output: 6
            #  *
            #  *  Input: grid = ["@Aa"]
            #  *  Output: -1
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.shortestPathAllKeys(grid)
            logging.info("Output: %d", retVal)

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
