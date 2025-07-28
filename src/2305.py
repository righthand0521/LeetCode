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
    def backtracking(self, i, distribute: List[int], cookies: List[int], k: int, zeroCount) -> int:
        retVal = float('inf')

        cookiesSize = len(cookies)

        if cookiesSize - i < zeroCount:
            return retVal

        if i == cookiesSize:
            retVal = max(distribute)
            return retVal

        for j in range(k):
            zeroCount -= int(distribute[j] == 0)
            distribute[j] += cookies[i]
            retVal = min(retVal, self.backtracking(
                i + 1, distribute, cookies, k, zeroCount))

            distribute[j] -= cookies[i]
            zeroCount += int(distribute[j] == 0)

        return retVal

    def distributeCookies(self, cookies: List[int], k: int) -> int:
        retVal = 0

        distribute = [0] * k
        retVal = self.backtracking(0, distribute, cookies, k, k)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for cookies, k in zip([[8, 15, 10, 20, 8], [6, 1, 3, 2, 2, 4, 1, 2]], [2, 3]):
            # /* Example
            #  *  Input: cookies = [8,15,10,20,8], k = 2
            #  *  Output: 31
            #  *
            #  *  Input: cookies = [6,1,3,2,2,4,1,2], k = 3
            #  *  Output: 7
            #  */
            logging.info("Input: cookies = %s, k = %s", cookies, k)

            retVal = pSolution.distributeCookies(cookies, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
