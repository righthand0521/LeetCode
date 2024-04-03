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
    def dfs(self, board: List[List[str]], word: str, row: int, col: int, idx: int) -> bool:
        retVal = False

        # 1 <= word.length <= 15
        if idx == len(word):
            retVal = True
            return retVal

        # m == board.length, n = board[i].length, 1 <= m, n <= 6
        if (row < 0) or (row > (len(board)-1)):
            return retVal
        elif (col < 0) or (col > (len(board[0])-1)):
            return retVal

        if board[row][col] != word[idx]:
            return retVal

        tmp = board[row][col]
        board[row][col] = ' '
        retVal = self.dfs(board, word, row-1, col, idx+1)
        retVal |= self.dfs(board, word, row+1, col, idx+1)
        retVal |= self.dfs(board, word, row, col-1, idx+1)
        retVal |= self.dfs(board, word, row, col+1, idx+1)
        board[row][col] = tmp

        return retVal

    def exist(self, board: List[List[str]], word: str) -> bool:
        retVal = False

        # m == board.length, n = board[i].length, 1 <= m, n <= 6
        boardSize = len(board)
        boardColSize = len(board[0])
        for row in range(boardSize):
            for col in range(boardColSize):
                retVal = self.dfs(board, word, row, col, 0)
                if retVal == True:
                    return retVal

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for board, word in zip([
            [["A", "B", "C", "E"], ["S", "F", "C", "S"], ["A", "D", "E", "E"]],
            [["A", "B", "C", "E"], ["S", "F", "C", "S"], ["A", "D", "E", "E"]],
            [["A", "B", "C", "E"], ["S", "F", "C", "S"], ["A", "D", "E", "E"]],
            [["A", "A"]],
            [["A"]]
        ], ["ABCCED", "SEE", "ABCB", "AAA", "A"]):
            # /* Example
            #  *  Input: Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
            #  *  Output: true
            #  *
            #  *  Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
            #  *  Output: true
            #  *
            #  *  Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
            #  *  Output: false
            #  *
            #  *  Input: board = [["A","A"]], word = "AAA"
            #  *  Output: false
            #  *
            #  *  Input: board = [["A"]], word = "A"
            #  *  Output: true
            #  */
            logging.info("Input: board = %s, word = %s", board, word)

            retVal = pSolution.exist(board, word)
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
