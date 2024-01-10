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
    def maxSubsequence(self, nums: List[int], k: int) -> List[int]:
        retVal = []

        sequence = [[index, value] for index, value in enumerate(nums)]
        sequence.sort(key=lambda sequence: -sequence[1])
        sequence = sequence[:k]
        sequence.sort(key=lambda sequence: sequence[0])
        retVal = [value for _, value in sequence]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[2, 1, 3, 3], [-1, -2, 3, 4], [3, 4, 3, 3]], [2, 3, 2]):
            # /* Example
            #  *  Input: nums = [2,1,3,3], k = 2
            #  *  Output: [3,3]
            #  *
            #  *  Input: nums = [-1,-2,3,4], k = 3
            #  *  Output: [-1,3,4]
            #  *
            #  *  Input: nums = [3,4,3,3], k = 2
            #  *  Output: [3,4]
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.maxSubsequence(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass

    sys.exit(0)
