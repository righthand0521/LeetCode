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
    def generateMatrix(self, n: int) -> List[List[int]]:
        retVal = [[0] * n for _ in range(n)]

        # /*
        #  *  (top,left)                              (top,right)
        #  *      +---------------------------------------+
        #  *      | 01(111) | 02(112) | 03(113) | 04(114) |
        #  *      | 12(142) | 13(211) | 14(212) | 05(121) |
        #  *      | 11(141) | 16(231) | 15(221) | 06(122) |
        #  *      | 10(133) | 09(132) | 08(131) | 07(123) |
        #  *      +---------------------------------------+
        #  * (down,left)                             (down,right)
        #  */
        left = 0
        right = n - 1
        top = 0
        down = n - 1
        num = 1
        while (left <= right) and (top <= down):
            for col in range(left, right + 1):
                retVal[top][col] = num
                num += 1

            for row in range(top + 1, down + 1):
                retVal[row][right] = num
                num += 1

            if (left < right) and (top < down):
                for col in range(right - 1, left, -1):
                    retVal[down][col] = num
                    num += 1

                for row in range(down, top, -1):
                    retVal[row][left] = num
                    num += 1

            left += 1
            right -= 1
            top += 1
            down -= 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [3, 1]:
            # /* Example
            #  *  Input: n = 3
            #  *  Output: [[1,2,3],[8,9,4],[7,6,5]]
            #  *
            #  *  Input: n = 1
            #  *  Output: [[1]]
            #  */
            logging.info("Input: n = %s", n)

            retVal = pSolution.generateMatrix(n)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
