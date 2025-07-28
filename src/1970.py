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
    def latestDayToCross(self, row: int, col: int, cells: List[List[int]]) -> int:
        retVal = 0

        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]

        left = 0
        right = row * col
        while left <= right:
            middle = (left + right) // 2

            grid = [[1] * col for _ in range(row)]
            for x, y in cells[:middle]:
                grid[x - 1][y - 1] = 0

            bfsQueue = deque()
            for i in range(col):
                if grid[0][i]:
                    bfsQueue.append((0, i))
                    grid[0][i] = 0

            found = False
            while bfsQueue:
                x, y = bfsQueue.popleft()

                for diffX, diffY in directions:
                    nextX = x + diffX
                    nextY = y + diffY

                    if (nextX < 0) or (nextX >= row):
                        continue
                    elif (nextY < 0) or (nextY >= col):
                        continue
                    elif grid[nextX][nextY] == 0:
                        continue

                    if nextX == row - 1:
                        found = True
                        break
                    bfsQueue.append((nextX, nextY))
                    grid[nextX][nextY] = 0

            if found == True:
                retVal = middle
                left = middle + 1
            else:
                right = middle - 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for row, col, cells in zip([2, 2, 3],
                                   [2, 2, 3],
                                   [[[1, 1], [2, 1], [1, 2], [2, 2]],
                                    [[1, 1], [1, 2], [2, 1], [2, 2]],
                                    [[1, 2], [2, 1], [3, 3], [2, 2], [1, 1], [1, 3], [2, 3], [3, 2], [3, 1]]]):
            # /* Example
            #  *  Input: row = 2, col = 2, cells = [[1,1],[2,1],[1,2],[2,2]]
            #  *  Output: 2
            #  *
            #  *  Input: row = 2, col = 2, cells = [[1,1],[1,2],[2,1],[2,2]]
            #  *  Output: 1
            #  *
            #  *  Input: row = 3, col = 3, cells = [[1,2],[2,1],[3,3],[2,2],[1,1],[1,3],[2,3],[3,2],[3,1]]
            #  *  Output: 3
            #  */
            logging.info("Input: row = %s, col = %s, cells = %s", row, col, cells)

            retVal = pSolution.latestDayToCross(row, col, cells)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
