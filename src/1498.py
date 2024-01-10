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
    def __init__(self):
        self.MODULO = 10 ** 9 + 7

    def numSubseq(self, nums: List[int], target: int) -> int:
        retVal = 0

        nums.sort()

        head = 0
        tail = len(nums) - 1
        while head <= tail:
            if nums[head] + nums[tail] > target:
                tail -= 1
                continue
            retVal += pow(2, (tail - head))
            retVal %= self.MODULO
            head += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, target in zip([[3, 5, 6, 7], [3, 3, 6, 8], [2, 3, 3, 4, 6, 7]], [9, 10, 12]):
            # /* Example
            #  *  Input: nums = [3,5,6,7], target = 9
            #  *  Output: 4
            #  *
            #  *  Input: nums = [3,3,6,8], target = 10
            #  *  Output: 6
            #  *
            #  *  Input: nums = [2,3,3,4,6,7], target = 12
            #  *  Output: 61
            #  */
            logging.info("Input: nums = %s, target = %s", nums, target)

            retVal = pSolution.numSubseq(nums, target)
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
