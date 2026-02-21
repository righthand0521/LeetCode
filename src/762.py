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
    def countPrimeSetBits(self, left: int, right: int) -> int:
        def isPrime(n):
            if n < 2:
                return False
            for i in range(2, int(n**0.5) + 1):
                if n % i == 0:
                    return False
            return True

        def countBits(n):
            count = 0
            while n:
                count += n & 1
                n >>= 1
            return count

        retVal = 0
        for i in range(left, right + 1):
            setBits = countBits(i)
            if isPrime(setBits):
                retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for left, right in [[6, 10], [10, 15]]:
            # /* Example
            #  *  Input: left = 6, right = 10
            #  *  Output: 4
            #  *
            #  *  Input: left = 10, right = 15
            #  *  Output: 5
            #  */
            logging.info("Input: left = %d, right = %d", left, right)

            retVal = pSolution.countPrimeSetBits(left, right)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
