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
    def search(self, nums: List[int], target: int) -> int:
        retVal = -1

        left = 0
        right = len(nums) - 1
        while left <= right:
            middle = left + (right - left) // 2
            if nums[middle] == target:
                retVal = middle
                break
            elif nums[middle] >= nums[left]:
                if (target >= nums[left]) and (target < nums[middle]):
                    right = middle - 1
                else:
                    left = middle + 1
            else:
                if (target <= nums[right]) and (target > nums[middle]):
                    left = middle + 1
                else:
                    right = middle - 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, target in zip([[4, 5, 6, 7, 0, 1, 2], [4, 5, 6, 7, 0, 1, 2], [1]], [0, 3, 0]):
            # /* Example
            #  *  Input: nums = [4,5,6,7,0,1,2], target = 0
            #  *  Output: 4
            #  *
            #  *  Input: nums = [4,5,6,7,0,1,2], target = 3
            #  *  Output: -1
            #  *
            #  *  Input: nums = [1], target = 0
            #  *  Output: -1
            #  */
            logging.info("Input: nums = %s, target = %s", nums, target)

            retVal = pSolution.search(nums, target)
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
