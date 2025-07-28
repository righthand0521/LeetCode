import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop

from functools import reduce


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
    def subtractProductAndSum(self, n: int) -> int:
        method = 1

        if method == 1:
            print("= math computing =")

            product = 1
            sum = 0
            while (n > 0):
                mod = n % 10
                product *= mod
                sum += mod
                n //= 10
            retVal = product - sum

            return retVal
        elif method == 2:
            print("= python function =")

            a = [int(x) for x in str(n)]
            return reduce((lambda x, y: x * y), a) - reduce((lambda x, y: x + y), a)


if __name__ == "__main__":
    logging_setting()

    logging.info("sys.version: %s", sys.version)
    print("")
    try:
        testCase = [
            Counter(n=234), Counter(n=4421)
        ]

        pSolution = Solution()
        for i in range(0, len(testCase)):
            print('Input: n = {}'.format(testCase[i]['n']))

            retVal = pSolution.subtractProductAndSum(testCase[i]['n'])
            print('Output: {}'.format(retVal))

            print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
