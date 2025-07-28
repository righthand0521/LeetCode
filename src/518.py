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
    def change(self, amount: int, coins: List[int]) -> int:
        retVal = 0

        dp = [0] * (amount+1)
        dp[0] = 1
        coinsSize = len(coins)
        for i in range(coinsSize):
            for j in range(coins[i], amount+1):
                dp[j] += dp[j - coins[i]]
        retVal = dp[amount]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for amount, coins in zip([5, 3, 10], [[1, 2, 5], [2], [10]]):
            # /* Example
            #  *  Input: amount = 5, coins = [1,2,5]
            #  *  Output: 4
            #  *
            #  *  Input: amount = 3, coins = [2]
            #  *  Output: 0
            #  *
            #  *  Input: amount = 10, coins = [10]
            #  *  Output: 1
            #  */
            logging.info("Input: amount = %s, coins = %s", amount, coins)

            retVal = pSolution.change(amount, coins)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
