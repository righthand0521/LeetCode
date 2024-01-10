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
    def climbStairs(self, n: int) -> int:
        retVal = 0

        # /* Climbing Stairs
        #  *  C[1] = 1; 1
        #  *  C[2] = 2; 1+1, 2
        #  *  C[n] = F[n-1] + F[n-2], n>=3.
        #  */
        CLIMBSTAIRS_1 = 1
        CLIMBSTAIRS_2 = 2
        CLIMBSTAIRS = 3
        dp = [0, CLIMBSTAIRS_1, CLIMBSTAIRS_2]

        retVal = dp[n % CLIMBSTAIRS]
        for i in range(CLIMBSTAIRS, n+1):
            dp[i % CLIMBSTAIRS] = dp[(i - 1) %
                                     CLIMBSTAIRS] + dp[(i - 2) % CLIMBSTAIRS]
            retVal = dp[i % CLIMBSTAIRS]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [2, 3, 4, 5, 6, 1, 45]:
            # /* Example
            #  *  Input: n = 2
            #  *  Output: 2
            #  *
            #  *  Input: n = 3
            #  *  Output: 3
            #  *
            #  *  Input: n = 4
            #  *  Output: 5
            #  *
            #  *  Input: n = 5
            #  *  Output: 8
            #  *
            #  *  Input: n = 6
            #  *  Output: 13
            #  *
            #  *  Input: n = 1
            #  *  Output: 1
            #  *
            #  *  Input: n = 45
            #  *  Output: 1836311903
            #  */
            logging.info("Input: n = %s", n)

            retVal = pSolution.climbStairs(n)
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
