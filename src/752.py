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
        self.nextSlot = {"0": "1", "1": "2", "2": "3", "3": "4",
                         "4": "5", "5": "6", "6": "7", "7": "8", "8": "9", "9": "0"}
        self.prevSlot = {"0": "9", "1": "0", "2": "1", "3": "2", "4": "3",
                         "5": "4", "6": "5", "7": "6", "8": "7", "9": "8"}

    def openLock(self, deadends: List[str], target: str) -> int:
        retVal = -1

        visitedCombinations = set(deadends)
        if "0000" in visitedCombinations:
            return retVal
        visitedCombinations.add("0000")

        retVal = 0
        pendingCombinations = deque()
        pendingCombinations.append("0000")
        while pendingCombinations:
            nodesCount = len(pendingCombinations)
            for _ in range(nodesCount):
                currentCombination = pendingCombinations.popleft()
                if currentCombination == target:
                    return retVal

                for wheel in range(4):
                    newCombination = list(currentCombination)
                    newCombination[wheel] = self.nextSlot[newCombination[wheel]]
                    newCombinationStr = "".join(newCombination)
                    if newCombinationStr not in visitedCombinations:
                        pendingCombinations.append(newCombinationStr)
                        visitedCombinations.add(newCombinationStr)

                    newCombination = list(currentCombination)
                    newCombination[wheel] = self.prevSlot[newCombination[wheel]]
                    newCombinationStr = "".join(newCombination)
                    if newCombinationStr not in visitedCombinations:
                        pendingCombinations.append(newCombinationStr)
                        visitedCombinations.add(newCombinationStr)

            retVal += 1

        retVal = - 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for deadends, target in [
            [["0201", "0101", "0102", "1212", "2002"], "0202"],
            [["8888"], "0009"],
            [["8887", "8889", "8878", "8898", "8788", "8988", "7888", "9888"], "8888"]
        ]:
            # /* Example
            #  *  Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
            #  *  Output: 6
            #  *
            #  *  Input: deadends = ["8888"], target = "0009"
            #  *  Output: 1
            #  *
            #  *  Input: deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
            #  *  Output: -1
            #  */
            logging.info("Input: deadends = %s, target = \"%s\"", deadends, target)

            retVal = pSolution.openLock(deadends, target)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
