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
    def findLexicographicallyLargestSequence(self, index, result, isNumberUsed, target):
        retVal = True

        # If we have filled all positions, return true indicating success
        resultSequenceSize = len(result)
        if index == resultSequenceSize:
            return retVal

        # If the current position is already filled, move to the next index
        if result[index] != 0:
            retVal = self.findLexicographicallyLargestSequence(index + 1, result, isNumberUsed, target)
            return retVal

        # Attempt to place numbers from target to 1 for a lexicographically largest result
        for numberToPlace in range(target, 0, -1):
            if isNumberUsed[numberToPlace]:
                continue
            isNumberUsed[numberToPlace] = True
            result[index] = numberToPlace

            # If placing number 1, move to the next index directly
            if numberToPlace == 1:
                if self.findLexicographicallyLargestSequence(index + 1, result, isNumberUsed, target) == True:
                    return retVal
            # Place larger numbers at two positions if valid
            elif (index + numberToPlace < resultSequenceSize) and (result[index + numberToPlace] == 0):
                result[index + numberToPlace] = numberToPlace
                if self.findLexicographicallyLargestSequence(index + 1, result, isNumberUsed, target) == True:
                    return retVal
                # Undo the placement for backtracking
                result[index + numberToPlace] = 0

            # Undo current placement and mark the number as unused
            result[index] = 0
            isNumberUsed[numberToPlace] = False

        retVal = False

        return retVal

    def constructDistancedSequence(self, n: int) -> List[int]:
        retVal = [0] * (2*n-1)

        # Keep track of which numbers are already placed in the sequence
        isNumberUsed = [False] * (n + 1)
        # Start recursive backtracking to construct the sequence
        self.findLexicographicallyLargestSequence(0, retVal, isNumberUsed, n)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [3, 5]:
            # /* Example
            #  *  Input: n = 3
            #  *  Output: [3,1,2,3,2]
            #  *
            #  *  Input: n = 5
            #  *  Output: [5,3,1,4,3,5,2,4,2]
            #  */
            logging.info("Input: n = %s", n)

            retVal = pSolution.constructDistancedSequence(n)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
