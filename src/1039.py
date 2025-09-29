import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop

from copy import deepcopy


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
    def minScoreTriangulation(self, values: List[int]) -> int:
        retVal = 0

        valuesSize = len(values)
        dp = [[0] * valuesSize for i in range(valuesSize)]
        for d in range(2, valuesSize):
            for i in range(valuesSize - d):
                j = i + d
                dp[i][j] = min(dp[i][k] + dp[k][j] + values[i] * values[j] * values[k] for k in range(i + 1, j))
        retVal = dp[0][valuesSize - 1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for values in [[1, 2, 3], [3, 7, 4, 5], [1, 3, 1, 4, 1, 5]]:
            # /* Example
            #  *  Input: values = [1,2,3]
            #  *  Output: 6
            #  *
            #  *  Input: values = [3,7,4,5]
            #  *  Output: 144
            #  *
            #  *  Input: values = [1,3,1,4,1,5]
            #  *  Output: 13
            #  */
            logging.info("Input: values = %s", values)

            retVal = pSolution.minScoreTriangulation(values)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
