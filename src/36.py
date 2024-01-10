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
    def isValidSudoku(self, board: List[List[str]]) -> bool:
        retVal = True

        boardSize = len(board)
        boardColSize = len(board[0])

        rowHashTable = [[0 for _ in range(boardColSize)] for _ in range(boardSize)]
        colHashTable = [[0 for _ in range(boardColSize)] for _ in range(boardSize)]
        boxHashTable = [[0 for _ in range(boardColSize)] for _ in range(boardSize)]
        for x in range(boardSize):
            for y in range(len(board[x])):
                if board[x][y] == ".":
                    continue

                digits = int(board[x][y]) - 1
                boxIndex = (x // 3) * 3 + y // 3
                if rowHashTable[x][digits] or colHashTable[y][digits] or boxHashTable[boxIndex][digits]:
                    retVal = False
                    return retVal

                rowHashTable[x][digits] = 1
                colHashTable[y][digits] = 1
                boxHashTable[boxIndex][digits] = 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for board in [[["5", "3", ".", ".", "7", ".", ".", ".", "."],
                       ["6", ".", ".", "1", "9", "5", ".", ".", "."],
                       [".", "9", "8", ".", ".", ".", ".", "6", "."],
                       ["8", ".", ".", ".", "6", ".", ".", ".", "3"],
                       ["4", ".", ".", "8", ".", "3", ".", ".", "1"],
                       ["7", ".", ".", ".", "2", ".", ".", ".", "6"],
                       [".", "6", ".", ".", ".", ".", "2", "8", "."],
                       [".", ".", ".", "4", "1", "9", ".", ".", "5"],
                       [".", ".", ".", ".", "8", ".", ".", "7", "9"]],
                      [["8", "3", ".", ".", "7", ".", ".", ".", "."],
                       ["6", ".", ".", "1", "9", "5", ".", ".", "."],
                       [".", "9", "8", ".", ".", ".", ".", "6", "."],
                       ["8", ".", ".", ".", "6", ".", ".", ".", "3"],
                       ["4", ".", ".", "8", ".", "3", ".", ".", "1"],
                       ["7", ".", ".", ".", "2", ".", ".", ".", "6"],
                       [".", "6", ".", ".", ".", ".", "2", "8", "."],
                       [".", ".", ".", "4", "1", "9", ".", ".", "5"],
                       [".", ".", ".", ".", "8", ".", ".", "7", "9"]]]:
            # /* Example
            #  *  Input: board =
            #  *  [["5","3",".",".","7",".",".",".","."]
            #  *  ,["6",".",".","1","9","5",".",".","."]
            #  *  ,[".","9","8",".",".",".",".","6","."]
            #  *  ,["8",".",".",".","6",".",".",".","3"]
            #  *  ,["4",".",".","8",".","3",".",".","1"]
            #  *  ,["7",".",".",".","2",".",".",".","6"]
            #  *  ,[".","6",".",".",".",".","2","8","."]
            #  *  ,[".",".",".","4","1","9",".",".","5"]
            #  *  ,[".",".",".",".","8",".",".","7","9"]]
            #  *  Output: true
            #  *
            #  *  Input: board =
            #  *  [["8","3",".",".","7",".",".",".","."]
            #  *  ,["6",".",".","1","9","5",".",".","."]
            #  *  ,[".","9","8",".",".",".",".","6","."]
            #  *  ,["8",".",".",".","6",".",".",".","3"]
            #  *  ,["4",".",".","8",".","3",".",".","1"]
            #  *  ,["7",".",".",".","2",".",".",".","6"]
            #  *  ,[".","6",".",".",".",".","2","8","."]
            #  *  ,[".",".",".","4","1","9",".",".","5"]
            #  *  ,[".",".",".",".","8",".",".","7","9"]]
            #  *  Output: false
            #  */
            logging.info("Input: board = [")
            for p in board:
                logging.info(" %s", p)
            logging.info("]")

            retVal = pSolution.isValidSudoku(board)
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
