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
    def longestSubsequence(self, arr: List[int], difference: int) -> int:
        retVal = 0

        # /* Input : arr = [1, 5, 7, 8, 5, 3, 4, 2, 1], difference = -2
        #  *  1 dp{1 : 1 }
        #  *  5 dp{1 : 1, 5 : 1 }
        #  *  7 dp{1 : 1, 5 : 1, 7 : 1 }
        #  *  8 dp{1 : 1, 5 : 1, 7 : 1, 8 : 1 }
        #  *  5 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1 }
        #  *  3 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1, 3 : 3 }
        #  *  4 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1, 3 : 3, 4 : 1 }
        #  *  2 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1, 3 : 3, 4 : 1, 2 : 2 }
        #  *  1 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1, 3 : 3, 4 : 1, 2 : 2, 1 : 4 }
        #  */
        dp = defaultdict(int)
        for value in arr:
            dp[value] = dp[value - difference] + 1
        retVal = max(dp.values())

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr, difference in zip([[1, 2, 3, 4], [1, 3, 5, 7], [1, 5, 7, 8, 5, 3, 4, 2, 1]], [1, 1, -2]):
            # /* Example
            #  *  Input: arr = [1,2,3,4], difference = 1
            #  *  Output: 4
            #  *
            #  *  Input: arr = [1,3,5,7], difference = 1
            #  *  Output: 1
            #  *
            #  *  Input: arr = [1,5,7,8,5,3,4,2,1], difference = -2
            #  *  Output: 4
            #  */
            logging.info("Input: arr = %s, difference = %s", arr, difference)

            retVal = pSolution.longestSubsequence(arr, difference)
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
