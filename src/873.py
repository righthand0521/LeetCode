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
    def lenLongestFibSubseq(self, arr: List[int]) -> int:
        retVal = 0

        arrSize = len(arr)

        # dp[prev][curr] stores length of Fibonacci sequence ending at indexes prev,curr
        dp = [[0] * arrSize for _ in range(arrSize)]

        # Find all possible pairs that sum to arr[curr]
        for curr in range(2, arrSize):
            # Use two pointers to find pairs that sum to arr[curr]
            start = 0
            end = curr - 1
            while start < end:
                pairSum = arr[start] + arr[end]
                if pairSum > arr[curr]:
                    end -= 1
                elif pairSum < arr[curr]:
                    start += 1
                else:  # Found a valid pair, update dp
                    dp[end][curr] = dp[start][end] + 1
                    retVal = max(retVal, dp[end][curr])
                    end -= 1
                    start += 1

        # Add 2 to include first two numbers, or return 0 if no sequence found
        if retVal != 0:
            retVal += 2

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr in [[1, 2, 3, 4, 5, 6, 7, 8], [1, 3, 7, 11, 12, 14, 18]]:
            # /* Example
            #  *  Input: arr = [1,2,3,4,5,6,7,8]
            #  *  Output: 5
            #  *
            #  *  Input: arr = [1,3,7,11,12,14,18]
            #  *  Output: 3
            #  */
            logging.info("Input: arr = %s", arr)

            retVal = pSolution.lenLongestFibSubseq(arr)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
