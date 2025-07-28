import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop

from random import choice


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
    def __init__(self) -> None:
        self.method = 1
        if self.method == 1:
            print("Heap")
        elif self.method == 2:
            print("Quickselect")    # https://en.wikipedia.org/wiki/Quickselect
        print()

    def findKthLargest(self, nums: List[int], k: int) -> int:
        retVal = 0

        if self.method == 1:      # Heap
            minHeap = []
            for num in nums:
                heappush(minHeap, num)
                if len(minHeap) > k:
                    heappop(minHeap)
            retVal = minHeap[0]
        elif self.method == 2:    # Quickselect
            def quick_select(nums, k):
                pivot = choice(nums)

                left = []
                middle = []
                right = []
                for num in nums:
                    if num > pivot:
                        left.append(num)
                    elif num < pivot:
                        right.append(num)
                    else:
                        middle.append(num)

                if k <= len(left):
                    return quick_select(left, k)

                if len(left) + len(middle) < k:
                    return quick_select(right, k - len(left) - len(middle))

                return pivot

            retVal = quick_select(nums, k)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[3, 2, 1, 5, 6, 4], [3, 2, 3, 1, 2, 4, 5, 5, 6]], [2, 4]):
            # /* Example
            #  *  Input: nums = [3,2,1,5,6,4], k = 2
            #  *  Output: 5
            #  *
            #  *  Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
            #  *  Output: 4
            #  */
            logging.info("Input: nums = %s, coins = %s", nums, k)

            retVal = pSolution.findKthLargest(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
