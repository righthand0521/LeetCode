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
    def maxSumAfterPartitioning(self, arr: List[int], k: int) -> int:
        retVal = 0

        arrSize = len(arr)

        dp = [0] * (arrSize + 1)
        for i in range(1, arrSize + 1):
            maxValue = arr[i - 1]
            for j in range(i - 1, max(-1, i - k - 1), -1):
                dp[i] = max(dp[i], dp[j] + maxValue * (i - j))
                if j > 0:
                    maxValue = max(maxValue, arr[j - 1])

        retVal = dp[arrSize]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr, k in zip([[1, 15, 7, 9, 2, 5, 10], [1, 4, 1, 5, 7, 3, 6, 1, 9, 9, 3], [1]], [3, 4, 1]):
            # /* Example
            #  *  Input: arr = [1,15,7,9,2,5,10], k = 3
            #  *  Output: 84
            #  *
            #  *  Input: arr = [1,4,1,5,7,3,6,1,9,9,3], k = 4
            #  *  Output: 83
            #  *
            #  *  Input: arr = [1], k = 1
            #  *  Output: 1
            #  */
            logging.info("Input: arr = %s, k = %s", arr, k)

            retVal = pSolution.maxSumAfterPartitioning(arr, k)
            logging.info("Output: %s", retVal)

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
