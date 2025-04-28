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
    def countSubarrays(self, nums: List[int], k: int) -> int:
        retVal = 0

        numsSize = len(nums)
        total = 0
        head = 0
        for tail in range(numsSize):
            total += nums[tail]
            while (head <= tail) and (total * (tail - head + 1) >= k):
                total -= nums[head]
                head += 1
            retVal += (tail - head + 1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[2, 1, 4, 3, 5], [1, 1, 1]], [10, 5]):
            # /* Example
            #  *  Input: nums = [2,1,4,3,5], k = 10
            #  *  Output: 6
            #  *
            #  *  Input: nums = [1,1,1], k = 5
            #  *  Output: 5
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.countSubarrays(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
