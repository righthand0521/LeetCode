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
    def rotate(self, nums: List[int], k: int) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """

        # Example: Input: nums = [1,2,3,4,5,6,7], k = 3; Output: [5,6,7,1,2,3,4]
        #   +---------+-------+    +-------+---------+    +-------+---------+    +-------+---------+
        #   | 1 2 3 4 | 5 6 7 | => | 7 6 5 | 4 3 2 1 | => | 5 6 7 | 4 3 2 1 | => | 5 6 7 | 1 2 3 4 |
        #   +---------+-------+    +-------+---------+    +-------+---------+    +-------+---------+
        numsSize = len(nums)
        k %= numsSize
        nums[:] = nums[::-1]
        nums[:k] = nums[:k][::-1]
        nums[k:] = nums[k:][::-1]


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[1, 2, 3, 4, 5, 6, 7], [-1, -100, 3, 99]], [3, 2]):
            # /* Example
            #  *  Input: nums = [1,2,3,4,5,6,7], k = 3
            #  *  Output: [5,6,7,1,2,3,4]
            #  *
            #  *  Input: nums = [-1,-100,3,99], k = 2
            #  *  Output: [3,99,-1,-100]
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            pSolution.rotate(nums, k)
            logging.info("Output: %s", nums)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
