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

        low = 0
        high = len(nums) - 1
        while (low <= high):
            mid = low + (high - low) // 2
            if target == nums[mid]:
                retVal = mid
                break
            elif target > nums[mid]:
                low = mid + 1
            elif target < nums[mid]:
                high = mid - 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print("")

        pSolution = Solution()
        for nums, target in zip([[-1, 0, 3, 5, 9, 12], [-1, 0, 3, 5, 9, 12], [5], [5], [2, 5], [2, 5], [2, 5]],
                                [9, 2, 5, 2, 2, 5, 0]):
            # /* Example
            #  *  Input: nums = [-1,0,3,5,9,12], target = 9
            #  *  Output: 4
            #  *
            #  *  Input: nums = [-1,0,3,5,9,12], target = 2
            #  *  Output: -1
            #  *
            #  *  Input: nums = [5], target = 5
            #  *  Output: 0
            #  *
            #  *  Input: nums = [5], target = 2
            #  *  Output: -1
            #  *
            #  *  Input: nums = [2,5], target = 2
            #  *  Output: 0
            #  *
            #  *  Input: nums = [2,5], target = 5
            #  *  Output: 1
            #  *
            #  *  Input: nums = [2,5], target = 0
            #  *  Output: -1
            #  */
            logging.info("Input: nums = %s, target = %d", nums, target)

            retVal = pSolution.search(nums, target)
            logging.info("Output: %d", retVal)

            print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass

    sys.exit(0)
