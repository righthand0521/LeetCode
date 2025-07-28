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
    def __init__(self) -> None:
        self.MODULO = 10 ** 9 + 7

    def checkRecord(self, n: int) -> int:
        retVal = 0

        dp = [[[0] * 3 for _ in range(2)] for _ in range(n + 1)]
        # Base case: there is 1 string of length 0 with zero 'A' and zero 'L'.
        dp[0][0][0] = 1

        # Iterate on smaller sub-problems and use the current smaller sub-problem
        # to generate results for bigger sub-problems.
        for length in range(n):
            for total_absences in range(2):
                for consecutive_lates in range(3):
                    # Store the count when 'P' is chosen.
                    dp[length + 1][total_absences][0] = (
                        dp[length + 1][total_absences][0] +
                        dp[length][total_absences][consecutive_lates]
                    ) % self.MODULO

                    # Store the count when 'A' is chosen.
                    if total_absences < 1:
                        dp[length + 1][total_absences + 1][0] = (
                            dp[length + 1][total_absences + 1][0] +
                            dp[length][total_absences][consecutive_lates]
                        ) % self.MODULO

                    # Store the count when 'L' is chosen.
                    if consecutive_lates < 2:
                        dp[length + 1][total_absences][consecutive_lates + 1] = (
                            dp[length + 1][total_absences][consecutive_lates + 1] +
                            dp[length][total_absences][consecutive_lates]
                        ) % self.MODULO

        # Sum up the counts for all combinations of length 'n' with different absent and late counts.
        for total_absences in range(2):
            for consecutive_lates in range(3):
                retVal = (
                    retVal +
                    dp[n][total_absences][consecutive_lates]
                ) % self.MODULO

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [2, 1, 10101]:
            # /* Example
            #  *  Input: n = 2
            #  *  Output: 8
            #  *
            #  *  Input: n = 1
            #  *  Output: 3
            #  *
            #  *  Input: n = 10101
            #  *  Output: 183236316
            #  */
            logging.info("Input: n = %s", n)

            retVal = pSolution.checkRecord(n)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
