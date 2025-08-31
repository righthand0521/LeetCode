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
    def __init__(self) -> None:
        self.boardSize = 9
        self.spaces = list()
        self.valid = False
        self.line = None
        self.column = None
        self.block = None

    def flip(self, i: int, j: int, digit: int):
        self.line[i] ^= (1 << digit)
        self.column[j] ^= (1 << digit)
        self.block[i // 3][j // 3] ^= (1 << digit)

    def dfs(self, board: List[List[str]], pos: int) -> None:
        spacesSize = len(self.spaces)
        if pos == spacesSize:
            self.valid = True
            return

        i, j = self.spaces[pos]
        mask = ~(self.line[i] | self.column[j] | self.block[i // 3][j // 3]) & (0x1ff)
        while mask:
            digitMask = mask & (-mask)
            digit = bin(digitMask).count("0") - 1
            self.flip(i, j, digit)
            board[i][j] = str(digit + 1)
            self.dfs(board, pos + 1)
            self.flip(i, j, digit)
            mask &= (mask - 1)
            if self.valid == True:
                return

    def solveSudoku(self, board: List[List[str]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        self.line = [0] * self.boardSize
        self.column = [0] * self.boardSize
        self.block = [[0] * 3 for _ in range(3)]
        self.valid = False

        for i in range(self.boardSize):
            for j in range(self.boardSize):
                if board[i][j] != ".":
                    digit = int(board[i][j]) - 1
                    self.flip(i, j, digit)

        while True:
            modified = False
            for i in range(self.boardSize):
                for j in range(self.boardSize):
                    if board[i][j] != ".":
                        continue
                    mask = ~(self.line[i] | self.column[j] | self.block[i // 3][j // 3]) & (0x1ff)
                    if not (mask & (mask - 1)):
                        digit = bin(mask).count("0") - 1
                        self.flip(i, j, digit)
                        board[i][j] = str(digit + 1)
                        modified = True
            if not modified:
                break

        for i in range(self.boardSize):
            for j in range(self.boardSize):
                if board[i][j] == ".":
                    self.spaces.append((i, j))

        self.dfs(board, 0)


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for board in [
            [
                ["5", "3", ".", ".", "7", ".", ".", ".", "."],
                ["6", ".", ".", "1", "9", "5", ".", ".", "."],
                [".", "9", "8", ".", ".", ".", ".", "6", "."],
                ["8", ".", ".", ".", "6", ".", ".", ".", "3"],
                ["4", ".", ".", "8", ".", "3", ".", ".", "1"],
                ["7", ".", ".", ".", "2", ".", ".", ".", "6"],
                [".", "6", ".", ".", ".", ".", "2", "8", "."],
                [".", ".", ".", "4", "1", "9", ".", ".", "5"],
                [".", ".", ".", ".", "8", ".", ".", "7", "9"]
            ]
        ]:
            # /* Example
            #  *  Input: board = [
            #  *      ["5","3",".",".","7",".",".",".","."],
            #  *      ["6",".",".","1","9","5",".",".","."],
            #  *      [".","9","8",".",".",".",".","6","."],
            #  *      ["8",".",".",".","6",".",".",".","3"],
            #  *      ["4",".",".","8",".","3",".",".","1"],
            #  *      ["7",".",".",".","2",".",".",".","6"],
            #  *      [".","6",".",".",".",".","2","8","."],
            #  *      [".",".",".","4","1","9",".",".","5"],
            #  *      [".",".",".",".","8",".",".","7","9"]
            #  *  ]
            #  *  Output: [
            #  *      ["5","3","4","6","7","8","9","1","2"],
            #  *      ["6","7","2","1","9","5","3","4","8"],
            #  *      ["1","9","8","3","4","2","5","6","7"],
            #  *      ["8","5","9","7","6","1","4","2","3"],
            #  *      ["4","2","6","8","5","3","7","9","1"],
            #  *      ["7","1","3","9","2","4","8","5","6"],
            #  *      ["9","6","1","5","3","7","2","8","4"],
            #  *      ["2","8","7","4","1","9","6","3","5"],
            #  *      ["3","4","5","2","8","6","1","7","9"]
            #  *  ]
            #  */
            logging.info("Input: board = [")
            for p in board:
                logging.info("  %s", p)
            logging.info("]")

            pSolution.solveSudoku(board)
            logging.info("Output:[")
            for p in board:
                logging.info(" %s", p)
            logging.info("]")

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
