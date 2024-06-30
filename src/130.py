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
    def solve(self, board: List[List[str]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        if board is None:
            return

        boardSize = len(board)
        boardColSize = len(board[0])

        bfsQueue = deque()
        for i in range(boardSize):
            if board[i][0] == "O":
                bfsQueue.append((i, 0))
                board[i][0] = "A"
            if board[i][boardColSize - 1] == "O":
                bfsQueue.append((i, boardColSize - 1))
                board[i][boardColSize - 1] = "A"
        for i in range(boardColSize - 1):
            if board[0][i] == "O":
                bfsQueue.append((0, i))
                board[0][i] = "A"
            if board[boardSize - 1][i] == "O":
                bfsQueue.append((boardSize - 1, i))
                board[boardSize - 1][i] = "A"

        while bfsQueue:
            row, col = bfsQueue.popleft()
            for x, y in [(row - 1, col), (row + 1, col), (row, col - 1), (row, col + 1)]:
                if (0 <= x < boardSize) and (0 <= y < boardColSize) and (board[x][y] == "O"):
                    bfsQueue.append((x, y))
                    board[x][y] = "A"

        for i in range(boardSize):
            for j in range(boardColSize):
                if board[i][j] == "A":
                    board[i][j] = "O"
                elif board[i][j] == "O":
                    board[i][j] = "X"


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for board in [[["X", "X", "X", "X"], ["X", "O", "O", "X"], ["X", "X", "O", "X"], ["X", "O", "X", "X"]], [["X"]]]:
            # /* Example
            #  *  Input: board = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
            #  *  Output: [["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]
            #  *
            #  *  Input: board = [["X"]]
            #  *  Output: [["X"]]
            #  */
            logging.info("Input: board = %s", board)

            pSolution.solve(board)
            logging.info("Output: %s", board)

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
