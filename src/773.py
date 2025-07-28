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
    def swap(self, state, i, j) -> str:
        retVal = ""

        stateList = list(state)
        stateList[i], stateList[j] = stateList[j], stateList[i]
        retVal = "".join(stateList)

        return retVal

    def slidingPuzzle(self, board: List[List[int]]) -> int:
        retVal = 0

        # Direction map for zero's possible moves in a 1D representation of the 2x3 board
        directions = [[1, 3], [0, 2, 4], [1, 5], [0, 4], [1, 3, 5], [2, 4],]
        target = "123450"

        startState = ""
        for rows in board:
            for cell in rows:
                startState += str(cell)
        bfsQueue = deque([startState])
        visited = set()  # To store visited states
        visited.add(startState)

        while bfsQueue:  # BFS to find the minimum number of moves
            queueSize = len(bfsQueue)
            for _ in range(queueSize):
                currentState = bfsQueue.popleft()
                if currentState == target:  # Check if we reached the target solved state
                    return retVal

                zeroPos = currentState.index("0")
                for newPos in directions[zeroPos]:
                    nextState = self.swap(currentState, zeroPos, newPos)
                    if nextState in visited:  # Skip if this state has been visited
                        continue

                    # Mark the new state as visited and add it to the bfsQueue
                    bfsQueue.append(nextState)
                    visited.add(nextState)

            retVal += 1

        retVal = -1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for board in [[[1, 2, 3], [4, 0, 5]], [[1, 2, 3], [5, 4, 0]], [[4, 1, 2], [5, 0, 3]]]:
            # /* Example
            #  *  Input: board = [[1,2,3],[4,0,5]]
            #  *  Output: 1
            #  *
            #  *  Input: board = [[1,2,3],[5,4,0]]
            #  *  Output: -1
            #  *
            #  *  Input: board = [[4,1,2],[5,0,3]]
            #  *  Output: 5
            #  */
            logging.info("Input: board = %s", board)

            retVal = pSolution.slidingPuzzle(board)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
