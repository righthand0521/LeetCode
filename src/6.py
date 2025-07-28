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
    def convert(self, s: str, numRows: int) -> str:
        retVal = ""

        if numRows == 1:
            retVal = s
            return retVal

        # /* numRows - 1 + numRows - 1 = 2 x numRows - 2 = 2 x (numRows - 1)
        #  *
        #  *  n = 3: 2x(3-1) = 4
        #  *  +-------+-------+----+
        #  *  | 0 |   | 4 |   | 8  |
        #  *  | 1 | 3 | 5 | 7 | 9  | ...
        #  *  | 2 |   | 6 |   | 10 |
        #  *  +-------+-------+----+
        #  *
        #  *  n = 4: 2x(4-1) = 6
        #  *  +-----------+-------------+----+
        #  *  | 0 |   |   | 6 |    |    | 12 |
        #  *  | 1 |   | 5 | 7 |    | 11 | 13 | ...
        #  *  | 2 | 4 |   | 8 | 10 |    | 14 |
        #  *  | 3 |   |   | 9 |    |    | 15 |
        #  *  +-----------+-------------+----+
        #  *
        #  *  n = 5: 2x(5-1) = 8
        #  *  +---------------+-------------------+----+
        #  *  | 0 |   |   |   |  8 |    |    |    | 16 |
        #  *  | 1 |   |   | 7 |  9 |    |    | 15 | 17 |
        #  *  | 2 |   | 6 |   | 10 |    | 14 |    | 18 | ...
        #  *  | 3 | 5 |   |   | 11 | 13 |    |    | 19 |
        #  *  | 4 |   |   |   | 12 |    |    |    | 20 |
        #  *  +---------------+-------------------+----+
        #  */
        sSize = len(s)
        charsInSection = 2 * (numRows - 1)
        for currRow in range(numRows):
            index = currRow
            while index < sSize:
                retVal += s[index]

                # // If currRow is not the first or last row then we have to add one more character of current section.
                if (currRow != 0) and (currRow != numRows - 1):
                    charsInBetween = charsInSection - 2 * currRow
                    secondIndex = index + charsInBetween
                    if secondIndex < sSize:
                        retVal += s[secondIndex]

                # // Jump to same row's first character of next section.
                index += charsInSection

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, numRows in [["PAYPALISHIRING", 3], ["PAYPALISHIRING", 4]]:
            # /* Example
            #  *  Input: s = "PAYPALISHIRING", numRows = 3
            #  *  Output: "PAHNAPLSIIGYIR"
            #  *
            #  *  Input: s = "PAYPALISHIRING", numRows = 4
            #  *  Output: "PINALSIGYAHRPI"
            #  */
            logging.info("Input: s = %s, numRows = %s", s, numRows)

            retVal = pSolution.convert(s, numRows)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
