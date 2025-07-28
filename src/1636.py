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
    def frequencySort(self, nums: List[int]) -> List[int]:
        retVal = []

        frequency = Counter(nums)
        retVal = sorted(nums, key=lambda x: (frequency[x], -x))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, 1, 2, 2, 2, 3], [2, 3, 1, 3, 2], [-1, 1, -6, 4, 5, -6, 1, 4, 1]]:
            # /* Example
            #  *  Input: nums = [1,1,2,2,2,3]
            #  *  Output: [3,1,1,2,2,2]
            #  *
            #  *  Input: nums = [2,3,1,3,2]
            #  *  Output: [1,3,3,2,2]
            #  *
            #  *  Input: nums = [-1,1,-6,4,5,-6,1,4,1]
            #  *  Output: [5,-1,4,4,-6,-6,1,1,1]
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.frequencySort(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
