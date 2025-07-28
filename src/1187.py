import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop
from math import inf


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
    def makeArrayIncreasing(self, arr1: List[int], arr2: List[int]) -> int:
        retVal = -1

        arr2 = sorted(set(arr2))

        arr1Size = len(arr1)
        arr2Size = len(arr2)

        dp = [[inf] * (min(arr2Size, arr1Size) + 1)
              for _ in range(arr1Size + 1)]
        dp[0][0] = -1

        for i in range(1, arr1Size + 1):
            for j in range(min(i, arr2Size) + 1):
                if arr1[i - 1] > dp[i - 1][j]:
                    dp[i][j] = arr1[i - 1]

                if j and (dp[i - 1][j - 1] != inf):
                    k = bisect_right(arr2, dp[i - 1][j - 1], j - 1)
                    if k < arr2Size:
                        dp[i][j] = min(dp[i][j], arr2[k])

                if (i == arr1Size) and (dp[i][j] != inf):
                    retVal = j
                    return retVal

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr1, arr2 in zip([[1, 5, 3, 6, 7], [1, 5, 3, 6, 7], [1, 5, 3, 6, 7]],
                              [[1, 3, 2, 4], [4, 3, 1], [1, 6, 3, 3]]):
            # /* Example
            #  *  Input: arr1 = [1,5,3,6,7], arr2 = [1,3,2,4]
            #  *  Output: 1
            #  *
            #  *  Input: arr1 = [1,5,3,6,7], arr2 = [4,3,1]
            #  *  Output: 2
            #  *
            #  *  Input: arr1 = [1,5,3,6,7], arr2 = [1,6,3,3]
            #  *  Output: -1
            #  */
            logging.info("Input: arr1 = %s, arr2 = %s", arr1, arr2)

            retVal = pSolution.makeArrayIncreasing(arr1, arr2)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
