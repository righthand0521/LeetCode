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
    def plusOne(self, digits: List[int]) -> List[int]:
        retVal = digits

        digitsSize = len(digits)
        for i in range(digitsSize-1, -1, -1):
            retVal[i] += 1
            if retVal[i] != 10:
                return retVal
            retVal[i] %= 10
        retVal = [1] + retVal

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for digits in [[1, 2, 3], [4, 3, 2, 1], [9]]:
            # /* Example
            #  *  Input: digits = [1,2,3]
            #  *  Output: [1,2,4]
            #  *
            #  *  Input: digits = [4,3,2,1]
            #  *  Output: [4,3,2,2]
            #  *
            #  *  Input: digits = [9]
            #  *  Output: [1,0]
            #  */
            logging.info("Input: digits = %s", digits)

            retVal = pSolution.plusOne(digits)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
