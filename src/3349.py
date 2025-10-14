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
    def hasIncreasingSubarrays(self, nums: List[int], k: int) -> bool:
        retVal = False

        numsSize = len(nums)

        current, previous, answer = 1, 0, 0
        for i in range(1, numsSize):
            if nums[i] > nums[i - 1]:
                current += 1
            else:
                previous = current
                current = 1
            answer = max(answer, min(previous, current))
            answer = max(answer, current // 2)

        retVal = (answer >= k)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in [[[2, 5, 7, 8, 9, 2, 3, 4, 3, 1], 3], [[1, 2, 3, 4, 4, 4, 4, 5, 6, 7], 5]]:
            # /* Example:
            #  *  Input: nums = [2, 5, 7, 8, 9, 2, 3, 4, 3, 1], k = 3
            #  *  Output: true
            #  *
            #  *  Input: nums = [1, 2, 3, 4, 4, 4, 4, 5, 6, 7], k = 5
            #  *  Output: false
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.hasIncreasingSubarrays(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
