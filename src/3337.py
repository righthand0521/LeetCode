import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from copy import deepcopy
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


class Mat:
    MODULO = 10 ** 9 + 7
    letterSize = 26    # s consists only of lowercase English letters.

    def __init__(self, copyFrom: "Mat" = None) -> None:
        self.a = [[0] * Mat.letterSize for _ in range(Mat.letterSize)]
        if copyFrom:
            for i in range(Mat.letterSize):
                for j in range(Mat.letterSize):
                    self.a[i][j] = copyFrom.a[i][j]

    def __mul__(self, other: "Mat") -> "Mat":
        retVal = Mat()

        for i in range(Mat.letterSize):
            for j in range(Mat.letterSize):
                for k in range(Mat.letterSize):
                    retVal.a[i][j] = (retVal.a[i][j] + self.a[i][k] * other.a[k][j]) % Mat.MODULO

        return retVal


class Solution:
    def __init__(self) -> None:
        self.MODULO = 10 ** 9 + 7
        self.letterSize = 26    # s consists only of lowercase English letters.

    def quickmul(self, x: Mat, y: int) -> Mat:  # matrix exponentiation by squaring
        retVal = Mat()

        # identity matrix
        for i in range(self.letterSize):
            retVal.a[i][i] = 1

        cur = x
        while y:
            if y & 1:
                retVal = retVal * cur
            cur = cur * cur
            y >>= 1

        return retVal

    def lengthAfterTransformations(self, s: str, t: int, nums: List[int]) -> int:
        retVal = 0

        T = Mat()
        for i in range(self.letterSize):
            for j in range(1, nums[i] + 1):
                T.a[(i + j) % self.letterSize][i] = 1

        res = self.quickmul(T, t)

        f = [0] * self.letterSize
        for ch in s:
            f[ord(ch) - ord("a")] += 1

        for i in range(self.letterSize):
            for j in range(self.letterSize):
                retVal = (retVal + res.a[i][j] * f[j]) % self.MODULO

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, t, nums in zip(["abcyy", "azbk"],
                              [2, 1],
                              [[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2],
                               [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2]]):
            # /* Example
            #  *  Input: s = "abcyy", t = 2, nums = [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2]
            #  *  Output: 7
            #  *
            #  *  Input: s = "azbk", t = 1, nums = [2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2]
            #  *  Output: 8
            #  */
            logging.info("Input: senate = \"%s\", t = %s, nums = %s", s, t, nums)

            retVal = pSolution.lengthAfterTransformations(s, t, nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
