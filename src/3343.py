import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from math import comb
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
    def __init__(self) -> None:
        self.MODULO = 10 ** 9 + 7

    def countBalancedPermutations(self, num: str) -> int:
        retVal = 0

        numSize = len(num)

        tot = 0
        cnt = [0] * 10
        for ch in num:
            d = int(ch)
            cnt[d] += 1
            tot += d
        if tot % 2 != 0:
            return retVal

        target = tot // 2
        maxOdd = (numSize + 1) // 2
        dp = [[0] * (maxOdd + 1) for _ in range(target + 1)]
        dp[0][0] = 1

        psum = 0
        totSum = 0
        for i in range(10):
            psum += cnt[i]  # Sum of the number of the first i digits
            totSum += i * cnt[i]  # Sum of the first i numbers

            oddCntStart = min(psum, maxOdd)
            oddCntEnd = max(0, psum - (numSize - maxOdd)) - 1
            for oddCnt in range(oddCntStart, oddCntEnd, -1):
                evenCnt = psum - oddCnt  # The number of bits that need to be filled in even numbered positions

                currStart = min(totSum, target)
                currEnd = max(0, totSum - target) - 1
                for curr in range(currStart, currEnd, -1):
                    res = 0

                    jStart = max(0, cnt[i] - evenCnt)
                    jEnd = min(cnt[i], oddCnt) + 1
                    for j in range(jStart, jEnd):
                        if i * j > curr:
                            break

                        # The current digit is filled with j positions at odd positions,
                        # and cnt[i] - j positions at even positions
                        ways = comb(oddCnt, j) * comb(evenCnt, cnt[i] - j) % self.MODULO
                        res = (res + ways * dp[curr - i * j][oddCnt - j] % self.MODULO) % self.MODULO

                    dp[curr][oddCnt] = res % self.MODULO

        retVal = dp[target][maxOdd]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for num in ["123", "112", "12345"]:
            # /* Example
            #  *  Input: num = "123"
            #  *  Output: 2
            #  *
            #  *  Input: num = "112"
            #  *  Output: 1
            #  *
            #  *  Input: num = "12345"
            #  *  Output: 0
            #  */
            logging.info("Input: num = \"%s\"", num)

            retVal = pSolution.countBalancedPermutations(num)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
