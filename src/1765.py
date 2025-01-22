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
    def highestPeak(self, isWater: List[List[int]]) -> List[List[int]]:
        retVal = []

        isWaterRows = len(isWater)
        isWaterCols = len(isWater[0])

        cellHeights = [[-1 for _ in range(isWaterCols)] for _ in range(isWaterRows)]
        bfsQueue = deque()
        for x in range(isWaterRows):
            for y in range(isWaterCols):
                if isWater[x][y] == 1:
                    cellHeights[x][y] = 0
                    bfsQueue.append((x, y))

        direction = [(0, 1), (0, -1), (1, 0), (-1, 0)]
        heightOfNextLayer = 1
        while bfsQueue:
            bfsQueueSize = len(bfsQueue)
            for _ in range(bfsQueueSize):
                currentCell = bfsQueue.popleft()

                for dx, dy in direction:
                    x = currentCell[0] + dx
                    y = currentCell[1] + dy
                    if (x < 0) or (x >= isWaterRows) or (y < 0) or (y >= isWaterCols):
                        continue
                    elif (cellHeights[x][y] != -1):
                        continue

                    cellHeights[x][y] = heightOfNextLayer
                    bfsQueue.append((x, y))

            heightOfNextLayer += 1

        retVal = cellHeights

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for isWater in [[[0, 1], [0, 0]], [[0, 0, 1], [1, 0, 0], [0, 0, 0]]]:
            # /* Example
            #  *  Input: isWater = [[0,1],[0,0]]
            #  *  Output: [[1,0],[2,1]]
            #  *
            #  *  Input: isWater = [[0,0,1],[1,0,0],[0,0,0]]
            #  *  Output: [[1,1,0],[0,1,1],[1,2,2]]
            #  */
            logging.info("Input: isWater = %s", isWater)

            retVal = pSolution.highestPeak(isWater)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
