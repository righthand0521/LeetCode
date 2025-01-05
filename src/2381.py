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
    def shiftingLetters(self, s: str, shifts: List[List[int]]) -> str:
        retVal = ""

        sSize = len(s)

        diffArray = [0] * sSize
        for start, end, direction in shifts:
            if direction == 1:
                diffArray[start] += 1
                if end + 1 < sSize:
                    diffArray[end + 1] -= 1
            else:
                diffArray[start] -= 1
                if end + 1 < sSize:
                    diffArray[end + 1] += 1

        numberOfShifts = 0
        for i in range(sSize):
            numberOfShifts = (numberOfShifts + diffArray[i]) % 26
            if numberOfShifts < 0:
                numberOfShifts += 26
            retVal += chr((ord(s[i]) - ord("a") +
                          numberOfShifts) % 26 + ord("a"))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, shifts in zip(["abc", "dztz"], [[[0, 1, 0], [1, 2, 1], [0, 2, 1]], [[0, 0, 0], [1, 1, 1]]]):
            # /* Example
            #  *  Input: s = "abc", shifts = [[0,1,0],[1,2,1],[0,2,1]]
            #  *  Output: "ace"
            #  *
            #  *  Input: s = "dztz", shifts = [[0,0,0],[1,1,1]]
            #  *  Output: "catz"
            #  */
            logging.info("Input: s = \"%s\", shifts = %s", s, shifts)

            retVal = pSolution.shiftingLetters(s, shifts)
            logging.info("Output: \"%s\"", retVal)

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
