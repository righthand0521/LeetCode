import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop
from math import gcd


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
    def maxScore(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        maxStates = 1 << numsSize
        finalMask = maxStates - 1
        dp = [0] * maxStates
        for state in range(finalMask, -1, -1):
            if state == finalMask:
                dp[state] = 0
                continue

            numbersTaken = bin(state).count('1')
            pairsFormed = numbersTaken // 2
            if numbersTaken % 2:
                continue

            for firstIndex in range(len(nums)):
                for secondIndex in range(firstIndex + 1, len(nums)):
                    if (state >> firstIndex & 1) == 1 or (state >> secondIndex & 1) == 1:
                        continue

                    currentScore = (pairsFormed + 1) * \
                        gcd(nums[firstIndex], nums[secondIndex])
                    stateAfterPickingCurrPair = state | (
                        1 << firstIndex) | (1 << secondIndex)
                    remainingScore = dp[stateAfterPickingCurrPair]
                    dp[state] = max(dp[state], currentScore + remainingScore)
        retVal = dp[0]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, 2], [3, 4, 6, 8], [1, 2, 3, 4, 5, 6]]:
            # /* Example
            #  *  Input: nums = [1,2]
            #  *  Output: 1
            #  *
            #  *  Input: nums = [3,4,6,8]
            #  *  Output: 11
            #  *
            #  *  Input: nums = [1,2,3,4,5,6]
            #  *  Output: 14
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.maxScore(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
