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
    def findEvenNumbers(self, digits: List[int]) -> List[int]:
        retVal = []

        nums = set()
        digitsSize = len(digits)
        for i in range(digitsSize):
            for j in range(digitsSize):
                for k in range(digitsSize):
                    if (i == j) or (i == k) or (j == k):
                        continue
                    num = digits[i] * 100 + digits[j] * 10 + digits[k]
                    if (num >= 100) and (num % 2 == 0):
                        nums.add(num)
        retVal = sorted(nums)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for digits in [[2, 1, 3, 0], [2, 2, 8, 8, 2], [3, 7, 5]]:
            # /* Example
            #  *  Input: digits = [2,1,3,0]
            #  *  Output: [102,120,130,132,210,230,302,310,312,320]
            #  *
            #  *  Input: digits = [2,2,8,8,2]
            #  *  Output: [222,228,282,288,822,828,882]
            #  *
            #  *  Input: digits = [3,7,5]
            #  *  Output: []
            #  */
            logging.info("Input: digits = %s", digits)

            retVal = pSolution.findEvenNumbers(digits)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
