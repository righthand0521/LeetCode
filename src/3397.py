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
    def maxDistinctElements(self, nums: List[int], k: int) -> int:
        retVal = 0

        nums.sort()

        previous = float('-inf')
        for num in nums:
            current = min(max(num - k, previous + 1), num + k)
            if current > previous:
                retVal += 1
                previous = current

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in [[[1, 2, 2, 3, 3, 4], 2], [[4, 4, 4, 4], 1]]:
            # /* Example
            #  *  Input: nums = [1,2,2,3,3,4], k = 2
            #  *  Output: 6
            #  *
            #  *  Input: nums = [4,4,4,4], k = 1
            #  *  Output: 3
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.maxDistinctElements(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
