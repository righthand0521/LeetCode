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
    def PredictTheWinner(self, nums: List[int]) -> bool:
        retVal = False

        # /* https://leetcode.cn/problems/predict-the-winner/solutions/396343/shou-hua-tu-jie-san-chong-xie-fa-di-gui-ji-yi-hua-/
        #  *  i = j: dp[i][j] = nums[i]
        #  *  i < j: dp[i][j] = max(nums[i] - dp[i + 1][j], nums[j] - dp[i][j - 1]
        #  *
        #  *  Example: nums = [1,5,2]
        #  *    | 1 5 2 | 1 5 2 | 1 5 2 | 1 5  2
        #  *  --+-------+-------+-------+--------
        #  *  1 | 1     | 1     | 1 4   | 1 4 -2
        #  *  5 | 0 5   | 0 5 3 | 0 5 3 | 0 5  3
        #  *  2 | 0 0 2 | 0 0 2 | 0 0 2 | 0 0  2
        #  *
        #  *  Example: nums = [1,5,233,7]
        #  *      | 1 5 233 7 | 1  5 233  7  | 1 5 233   7  | 1 5 233   7
        #  *  ----+-----------+--------------+--------------+-------------
        #  *   1  | 1         | 1            | 1            | 1 4 229  222
        #  *   5  | 0 5       | 0  5         | 0 5 228 -221 | 0 5 229 -221
        #  *  233 | 0 0 233   | 0  0 233 226 | 0 0 233  226 | 0 0 233  226
        #  *   7  | 0 0  0  7 | 0  0  0   7  | 0 0  0    7  | 0 0  0    7
        #  */
        numsSize = len(nums)
        dp = [[0] * numsSize for _ in range(numsSize)]

        for i in range(numsSize):
            dp[i][i] = nums[i]

        for i in range(numsSize - 2, -1, -1):
            for j in range(i + 1, numsSize):
                dp[i][j] = max(nums[i] - dp[i + 1][j], nums[j] - dp[i][j - 1])

        if dp[0][numsSize - 1] >= 0:
            retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, 5, 2], [1, 5, 233, 7]]:
            # /* Example
            #  *  Input: nums = [1,5,2]
            #  *  Output: false
            #  *
            #  *  Input: nums = [1,5,233,7]
            #  *  Output: true
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.PredictTheWinner(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
