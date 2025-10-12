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
    def __init__(self):
        self.MODULO = 10 ** 9 + 7

    def quickmul(self, x: int, y: int) -> int:
        retVal = 1

        current = x % self.MODULO
        while y:
            if y & 1:
                retVal = retVal * current % self.MODULO
            y >>= 1
            current = current * current % self.MODULO

        return retVal

    def magicalSum(self, m: int, k: int, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        fac = [1] * (m + 1)
        for i in range(1, m + 1):
            fac[i] = fac[i - 1] * i % self.MODULO

        ifac = [1] * (m + 1)
        for i in range(2, m + 1):
            ifac[i] = self.quickmul(i, self.MODULO - 2)
        for i in range(2, m + 1):
            ifac[i] = ifac[i - 1] * ifac[i] % self.MODULO

        numsPower = [[1] * (m + 1) for _ in range(numsSize)]
        for i in range(numsSize):
            for j in range(1, m + 1):
                numsPower[i][j] = numsPower[i][j - 1] * nums[i] % self.MODULO

        f = [[[[0] * (k + 1) for _ in range(m * 2 + 1)] for _ in range(m + 1)] for _ in range(numsSize)]
        for j in range(m + 1):
            f[0][j][j][0] = numsPower[0][j] * ifac[j] % self.MODULO

        for i in range(numsSize - 1):
            for j in range(m + 1):
                for p in range(m * 2 + 1):
                    for q in range(k + 1):
                        if f[i][j][p][q] == 0:
                            continue

                        q2 = (p % 2) + q
                        if q2 > k:
                            break

                        for r in range(m - j + 1):
                            p2 = (p // 2) + r
                            if p2 > m * 2:
                                continue

                            tmp = f[i][j][p][q] * numsPower[i + 1][r] % self.MODULO * ifac[r] % self.MODULO
                            f[i + 1][j + r][p2][q2] = (f[i + 1][j + r][p2][q2] + tmp) % self.MODULO

        for p in range(m * 2 + 1):
            for q in range(k + 1):
                if bin(p).count("1") + q == k:
                    retVal = (retVal + f[numsSize - 1][m][p][q] * fac[m] % self.MODULO) % self.MODULO

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for m, k, nums in [[5, 5, [1, 10, 100, 10000, 1000000]], [2, 2, [5, 4, 3, 2, 1]], [1, 1, [28]]]:
            # /* Example
            #  *  Input: m = 5, k = 5, nums = [1,10,100,10000,1000000]
            #  *  Output: 991600007
            #  *
            #  *  Input: m = 2, k = 2, nums = [5,4,3,2,1]
            #  *  Output: 170
            #  *
            #  *  Input: m = 1, k = 1, nums = [28]
            #  *  Output: 28
            #  */
            logging.info("Input: m = %s, k = %s, nums = %s", m, k, nums)

            retVal = pSolution.magicalSum(m, k, nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
