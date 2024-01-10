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
    def twoSum(self, numbers: List[int], target: int) -> List[int]:
        retVal = []

        left = 0
        right = len(numbers) - 1
        sum = numbers[left] + numbers[right]
        while sum != target:
            if sum > target:
                right -= 1
            elif sum < target:
                left += 1
            sum = numbers[left] + numbers[right]
        retVal = [left+1, right+1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, target in zip([[2, 7, 11, 15], [2, 3, 4], [-1, 0]], [9, 6, -1]):
            # /* Example
            #  *  Input: nums = [2,7,11,15], target = 9
            #  *  Output: [1,2]
            #  *
            #  *  Input: numbers = [2,3,4], target = 6
            #  *  Output: [1,3]
            #  *
            #  *  Input: nums = [-1,0], target = -1
            #  *  Output: [1,2]
            #  */
            logging.info("Input: nums = %s, target = %s", nums, target)

            retVal = pSolution.twoSum(nums, target)
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
