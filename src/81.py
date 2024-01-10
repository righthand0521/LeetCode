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
    def search(self, nums: List[int], target: int) -> bool:
        retVal = False

        left = 0
        right = len(nums) - 1
        while left <= right:
            middle = left + (right - left) // 2
            if nums[middle] == target:
                retVal = True
                break
            elif (nums[middle] == nums[left]) and (nums[middle] == nums[right]):
                left += 1
                right -= 1
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
        for nums, target in zip([[2, 5, 6, 0, 0, 1, 2], [2, 5, 6, 0, 0, 1, 2]], [0, 3]):
            # /* Example
            #  *  Input: nums = [2,5,6,0,0,1,2], target = 0
            #  *  Output: true
            #  *
            #  *  Input: nums = [2,5,6,0,0,1,2], target = 3
            #  *  Output: false
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
