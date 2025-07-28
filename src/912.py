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
    def mergeSort(self, nums: List[int], left: int, right: int) -> None:
        if left == right:
            return

        middle = (left + right) // 2
        self.mergeSort(nums, left, middle)
        self.mergeSort(nums, middle + 1, right)

        tmp = []
        i = left
        j = middle + 1
        while (i <= middle) or (j <= right):
            if (i > middle) or ((j <= right) and (nums[j] < nums[i])):
                tmp.append(nums[j])
                j += 1
            else:
                tmp.append(nums[i])
                i += 1
        nums[left: right + 1] = tmp

    def sortArray(self, nums: List[int]) -> List[int]:
        retVal = nums

        self.mergeSort(retVal, 0, len(retVal) - 1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[5, 2, 3, 1], [5, 1, 1, 2, 0, 0]]:
            # /* Example
            #  *  Input: nums = [5,2,3,1]
            #  *  Output: [1,2,3,5]
            #  *
            #  *  Input: nums = [5,1,1,2,0,0]
            #  *  Output: [0,0,1,1,2,5]
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.sortArray(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
