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
    def minDifficulty(self, jobDifficulty: List[int], d: int) -> int:
        retVal = -1

        jobDifficultySize = len(jobDifficulty)
        if jobDifficultySize < d:
            return retVal

        maxDifficulty = 0
        dp = [0] * jobDifficultySize
        for i in range(jobDifficultySize):
            maxDifficulty = max(maxDifficulty, jobDifficulty[i])
            dp[i] = maxDifficulty

        for i in range(1, d):
            dpNext = [0] * jobDifficultySize

            monotonicStack = []
            for j in range(i, jobDifficultySize):
                minDifficulty = dp[j - 1]
                while monotonicStack and jobDifficulty[monotonicStack[-1][0]] < jobDifficulty[j]:
                    minDifficulty = min(minDifficulty, monotonicStack[-1][1])
                    monotonicStack.pop()

                if monotonicStack:
                    dpNext[j] = min(dpNext[monotonicStack[-1][0]], minDifficulty + jobDifficulty[j])
                else:
                    dpNext[j] = minDifficulty + jobDifficulty[j]

                monotonicStack.append((j, minDifficulty))

            dp = dpNext

        retVal = dp[jobDifficultySize - 1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for jobDifficulty, d in zip([[6, 5, 4, 3, 2, 1], [9, 9, 9], [1, 1, 1]], [2, 4, 3]):
            # /* Example
            #  *  Input: jobDifficulty = [6,5,4,3,2,1], d = 2
            #  *  Output: 7
            #  *
            #  *  Input: jobDifficulty = [9,9,9], d = 4
            #  *  Output: -1
            #  *
            #  *  Input: jobDifficulty = [1,1,1], d = 3
            #  *  Output: 3
            #  */
            logging.info("Input: jobDifficulty = %s, d = %s", jobDifficulty, d)

            retVal = pSolution.minDifficulty(jobDifficulty, d)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
