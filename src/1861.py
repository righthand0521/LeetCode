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
    def rotateTheBox(self, box: List[List[str]]) -> List[List[str]]:
        retVal = []

        boxSize = len(box)
        boxColSize = len(box[0])
        retVal = [["." for _ in range(boxSize)] for _ in range(boxColSize)]

        # Apply gravity to let stones fall to the lowest possible empty cell in each column
        for i in range(boxSize):
            lowestRowWithEmptyCell = boxColSize - 1

            # Process each cell in row 'i' in reversed order
            for j in range(boxColSize - 1, -1, -1):
                # Found a stone - let it fall to the lowest empty cell
                if box[i][j] == "#":
                    # Place it in the correct position in the rotated grid
                    retVal[lowestRowWithEmptyCell][boxSize - i - 1] = "#"
                    lowestRowWithEmptyCell -= 1

                # Found an obstacle - reset 'lowestRowWithEmptyCell' to the row directly above it
                if box[i][j] == "*":
                    # Place the obstacle in the correct position in the rotated grid
                    retVal[j][boxSize - i - 1] = "*"
                    lowestRowWithEmptyCell = j - 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for box in [[["#", ".", "#"]],
                    [["#", ".", "*", "."], ["#", "#", "*", "."]],
                    [["#", "#", "*", ".", "*", "."], ["#", "#", "#", "*", ".", "."], ["#", "#", "#", ".", "#", "."]]]:
            # /* Example
            #  *  Input: box = [["#",".","#"]]
            #  *  Output: [["."],["#"],["#"]]
            #  *
            #  *  Input: box = [["#",".","*","."],["#","#","*","."]]
            #  *  Output: [["#","."],["#","#"],["*","*"],[".","."]]
            #  *
            #  *  Input: box = [["#","#","*",".","*","."],["#","#","#","*",".","."],["#","#","#",".","#","."]]
            #  *  Output: [[".","#","#"],[".","#","#"],["#","#","*"],["#","*","."],["#",".","*"],["#",".","."]]
            #  */
            logging.info("Input: box = %s", box)

            retVal = pSolution.rotateTheBox(box)
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
