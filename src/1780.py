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
    def checkPowersOfThree(self, n: int) -> bool:
        retVal = False

        # 可以將 n 轉換成 3 進位
        # 如果 n 的 3 進制表示中每一位均不為 2, 那麼答案為 True, 否則為 False.
        # 例如, 當 n = 12 時, 12 = 110, 滿足要求; 當 n = 21 時, 21 = 210, 不滿足要求.
        while n > 0:
            if n % 3 == 2:  # Check if this power should be used twice
                return retVal
            n //= 3  # Divide n by 3 to move to the next greater power
        retVal = True  # The ternary representation of n consists only of 0s and 1s

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [12, 91, 21]:
            # /* Example
            #  *  Input: n = 12
            #  *  Output: true
            #  *
            #  *  Input: n = 91
            #  *  Output: true
            #  *
            #  *  Input: n = 21
            #  *  Output: false
            #  */
            logging.info("Input: n = %s", n)

            retVal = pSolution.checkPowersOfThree(n)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
