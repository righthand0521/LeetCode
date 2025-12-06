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
    def __init__(self):
        self.MODULO = 10 ** 9 + 7

    def countPartitions(self, nums: List[int], k: int) -> int:
        retVal = 0

        numsSize = len(nums)

        dp = [0] * (numsSize + 1)
        dp[0] = 1
        prefix = [0] * (numsSize + 1)
        prefix[0] = 1
        minQueue = deque()
        maxQueue = deque()

        j = 0
        for i in range(numsSize):
            # maintain the maximum value queue
            while (maxQueue) and (nums[maxQueue[-1]] <= nums[i]):
                maxQueue.pop()
            maxQueue.append(i)

            # maintain the minimum value queue
            while (minQueue) and (nums[minQueue[-1]] >= nums[i]):
                minQueue.pop()
            minQueue.append(i)

            # adjust window
            while (maxQueue) and (minQueue) and (nums[maxQueue[0]] - nums[minQueue[0]] > k):
                if maxQueue[0] == j:
                    maxQueue.popleft()
                if minQueue[0] == j:
                    minQueue.popleft()
                j += 1

            if j > 0:
                dp[i + 1] = (prefix[i] - prefix[j - 1] + self.MODULO) % self.MODULO
            else:
                dp[i + 1] = prefix[i] % self.MODULO

            prefix[i + 1] = (prefix[i] + dp[i + 1]) % self.MODULO

        retVal = dp[numsSize]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in [[[9, 4, 1, 3, 7], 4], [[3, 3, 4], 0]]:
            # /* Example
            #  *  Input: nums = [9,4,1,3,7], k = 4
            #  *  Output: 6
            #  *
            #  *  Input: nums = [3,3,4], k = 0
            #  *  Output: 2
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.countPartitions(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
