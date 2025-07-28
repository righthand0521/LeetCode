import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from math import gcd
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
    def halfToPalindrome(self, left: int, even: bool) -> int:
        retVal = left

        if not even:
            left = left // 10

        while left > 0:
            retVal = retVal * 10 + left % 10
            left //= 10

        return retVal

    def nearestPalindromic(self, n: str) -> str:
        retVal = ""

        nSize = len(n)

        i = nSize // 2 - 1 if nSize % 2 == 0 else nSize // 2
        firstHalf = int(n[: i + 1])

        # Generate possible palindromic candidates:
        #   1. Create a palindrome by mirroring the first half.
        #   2. Create a palindrome by mirroring the first half incremented by 1.
        #   3. Create a palindrome by mirroring the first half decremented by 1.
        #   4. Handle edge cases by considering palindromes of the
        #      form 999...and 100...001 (smallest and largest n-digit palindromes).
        candidates = []
        candidates.append(self.halfToPalindrome(firstHalf, nSize % 2 == 0))
        candidates.append(self.halfToPalindrome(firstHalf + 1, nSize % 2 == 0))
        candidates.append(self.halfToPalindrome(firstHalf - 1, nSize % 2 == 0))
        candidates.append(10 ** (nSize - 1) - 1)
        candidates.append(10**nSize + 1)

        diff = float("inf")
        res = 0
        nl = int(n)
        for candidate in candidates:
            if candidate == nl:
                continue

            if abs(candidate - nl) < diff:
                diff = abs(candidate - nl)
                res = candidate
            elif abs(candidate - nl) == diff:
                res = min(res, candidate)

        retVal = str(res)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in ["123", "1"]:
            # /* Example
            #  *  Input: n = "123"
            #  *  Output: "121"
            #  *
            #  *  Input: n = "1"
            #  *  Output: "0"
            #  */
            logging.info("Input: n = \"%s\"", n)

            retVal = pSolution.nearestPalindromic(n)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
