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
        self.TARGET = 24
        self.EPSILON = 1e-6
        self.ADD = 0
        self.MULTIPLY = 1
        self.SUBTRACT = 2
        self.DIVIDE = 3

    def backtracking(self, cards: List[int]) -> bool:
        retVal = False

        if not cards:
            return retVal

        cardsSize = len(cards)
        if cardsSize == 1:
            retVal = abs(cards[0] - self.TARGET) < self.EPSILON
            return retVal

        for i, x in enumerate(cards):
            for j, y in enumerate(cards):
                if i == j:
                    continue

                newCards = list()
                for k, z in enumerate(cards):
                    if (k != i) and (k != j):
                        newCards.append(z)

                for k in range(4):
                    if (k < 2) and (i > j):
                        continue

                    if k == self.ADD:
                        newCards.append(x + y)
                    elif k == self.MULTIPLY:
                        newCards.append(x * y)
                    elif k == self.SUBTRACT:
                        newCards.append(x - y)
                    elif k == self.DIVIDE:
                        if abs(y) < self.EPSILON:
                            continue
                        newCards.append(x / y)

                    if self.backtracking(newCards) == True:
                        retVal = True
                        return retVal

                    newCards.pop()

        return retVal

    def judgePoint24(self, cards: List[int]) -> bool:
        retVal = False

        retVal = self.backtracking(cards)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for cards in [[4, 1, 8, 7], [1, 2, 1, 2]]:
            # /* Example
            #  *  Input: cards = [4,1,8,7]
            #  *  Output: true
            #  *
            #  *  Input: cards = [1,2,1,2]
            #  *  Output: false
            #  */
            logging.info("Input: cards = %s", cards)

            retVal = pSolution.judgePoint24(cards)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
