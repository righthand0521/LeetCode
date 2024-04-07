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
        self.row = 0
        self.col = 0

    def getCoordinate(self, boardSize: int, s: int) -> None:
        self.row = boardSize - 1 - (s - 1) // boardSize
        self.col = (s - 1) % boardSize

        if (((boardSize % 2 == 1) and (self.row % 2 == 1)) or ((boardSize % 2 == 0) and (self.row % 2 == 0))):
            self.col = boardSize - 1 - self.col

    def snakesAndLadders(self, board: List[List[int]]) -> int:
        retVal = -1

        boardSize = len(board)
        seenSize = boardSize * boardSize + 1
        seen = [False] * seenSize
        seen[1] = True

        bfsQueue = deque([(1, 0)])
        while bfsQueue:
            s, dist = bfsQueue.popleft()
            if s == (seenSize - 1):
                retVal = dist
                return retVal

            self.row = 0
            self.col = 0
            for i in range(1, 7):
                if (s + i) >= seenSize:
                    break

                self.getCoordinate(boardSize, s + i)
                if board[self.row][self.col] == -1:
                    sfinal = s + i
                else:
                    sfinal = board[self.row][self.col]

                if seen[sfinal] == False:
                    seen[sfinal] = True
                    bfsQueue.append((sfinal, dist + 1))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for board in [[[-1, -1, -1, -1, -1, -1], [-1, -1, -1, -1, -1, -1], [-1, -1, -1, -1, -1, -1],
                       [-1, 35, -1, -1, 13, -1], [-1, -1, -1, -1, -1, -1], [-1, 15, -1, -1, -1, -1]],
                      [[-1, -1], [-1, 3]]]:
            # /* Example
            #  *  Input: board = [
            #  *      [-1,-1,-1,-1,-1,-1],
            #  *      [-1,-1,-1,-1,-1,-1],
            #  *      [-1,-1,-1,-1,-1,-1],
            #  *      [-1,35,-1,-1,13,-1],
            #  *      [-1,-1,-1,-1,-1,-1],
            #  *      [-1,15,-1,-1,-1,-1]
            #  *  ]
            #  *  Output: 4
            #  *
            #  *  Input: board = [[-1,-1],[-1,3]]
            #  *  Output: 1
            #  */
            logging.info("Input: board = %s", board)

            retVal = pSolution.snakesAndLadders(board)
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
