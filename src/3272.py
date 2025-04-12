import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from math import factorial
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
    def countGoodIntegers(self, n: int, k: int) -> int:
        retVal = 0

        # Enumerate the number of palindrome numbers of n digits
        base = 10 ** ((n - 1) // 2)
        skip = n & 1
        dictionary = set()
        for i in range(base, base * 10):
            s = str(i)
            s += s[::-1][skip:]
            palindromicInteger = int(s)

            # If the current palindrome number is a k-palindromic integer
            if palindromicInteger % k == 0:
                sorted_s = "".join(sorted(s))
                dictionary.add(sorted_s)

        fac = [factorial(i) for i in range(n + 1)]
        for s in dictionary:
            cnt = [0] * 10
            for c in s:
                cnt[int(c)] += 1

            # Calculate permutations and combinations
            tot = (n - cnt[0]) * fac[n - 1]
            for x in cnt:
                tot //= fac[x]
            retVal += tot

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, k in zip([3, 1, 5], [5, 4, 6]):
            # /* Example
            #  *  Input: n = 3, k = 5
            #  *  Output: 27
            #  *
            #  *  Input: n = 1, k = 4
            #  *  Output: 2
            #  *
            #  *  Input: n = 5, k = 6
            #  *  Output: 2468
            #  */
            logging.info("Input: n = %s, k = %s", n, k)

            retVal = pSolution.countGoodIntegers(n, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
