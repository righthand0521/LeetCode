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
    def generateBoard(self, n: int, queens: List[int], board: List[str]):
        retVal = []

        for i in range(n):
            board[queens[i]] = "Q"
            retVal.append("".join(board))
            board[queens[i]] = "."

        return retVal

    def backtrack(self, n: int, row: int,
                  queens: List[int], columns: set, diagonal1: set, diagonal2: set, board: List[str],
                  answer: List[List[str]]) -> None:
        if row == n:
            answer.append(self.generateBoard(n, queens, board))
            return

        for i in range(n):
            if (i in columns) or ((row - i) in diagonal1) or ((row + i) in diagonal2):
                continue

            queens[row] = i
            columns.add(i)
            diagonal1.add(row - i)
            diagonal2.add(row + i)
            self.backtrack(n, row + 1, queens, columns, diagonal1, diagonal2, board, answer)
            columns.remove(i)
            diagonal1.remove(row - i)
            diagonal2.remove(row + i)

    def solveNQueens(self, n: int) -> List[List[str]]:
        retVal = []

        queens = [-1] * n
        columns = set()
        diagonal1 = set()
        diagonal2 = set()
        board = ["."] * n
        self.backtrack(n, 0, queens, columns, diagonal1, diagonal2, board, retVal)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [4, 1]:
            # /* Example
            #  *  Input: n = 4
            #  *  Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
            #  *
            #  *  Input: n = 1
            #  *  Output: [["Q"]]
            #  */
            logging.info("Input: n = %s", n)

            retVal = pSolution.solveNQueens(n)
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
