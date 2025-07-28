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
    def gameOfLife(self, board: List[List[int]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        # m == board.length, n == board[i].length, 1 <= m, n <= 25
        rowSize = len(board)
        colSize = len(board[0])

        backup = [[board[x][y] for y in range(colSize)] for x in range(rowSize)]

        for x in range(rowSize):
            for y in range(colSize):
                live = 0
                for i in range(-1, 2):
                    neighborX = x + i
                    if (neighborX < 0) or (neighborX >= rowSize):
                        continue

                    for j in range(-1, 2):
                        if (i == 0) and (j == 0):
                            continue

                        neighborY = y + j
                        if (neighborY < 0) or (neighborY >= colSize):
                            continue

                        if backup[neighborX][neighborY] == 1:
                            live += 1

                if backup[x][y] == 1:
                    if (live < 2) or (live > 3):
                        board[x][y] = 0
                elif backup[x][y] == 0:
                    if live == 3:
                        board[x][y] = 1


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for board in [[[0, 1, 0], [0, 0, 1], [1, 1, 1], [0, 0, 0]], [[1, 1], [1, 0]]]:
            # /* Example
            #  *  Input: board = [[0,1,0],[0,0,1],[1,1,1],[0,0,0]]
            #  *  Output: [[0,0,0],[1,0,1],[0,1,1],[0,1,0]]
            #  *
            #  *  Input: board = [[1,1],[1,0]]
            #  *  Output: [[1,1],[1,1]]
            #  */
            logging.info("Input: board = %s", board)

            pSolution.gameOfLife(board)
            logging.info("Output: %s", board)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
