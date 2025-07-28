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
    def atMostDifferent(self, nums: List[int], k: int) -> int:
        retVal = 0

        hashTable = defaultdict(int)
        left = 0
        for right, rightValue in enumerate(nums):
            hashTable[rightValue] += 1

            hashTableSize = len(hashTable)
            while hashTableSize > k:
                leftValue = nums[left]
                hashTable[leftValue] -= 1
                if hashTable[leftValue] == 0:
                    del hashTable[leftValue]
                    hashTableSize = len(hashTable)
                left += 1

            retVal += (right - left)

        return retVal

    def subarraysWithKDistinct(self, nums: List[int], k: int) -> int:
        retVal = 0

        # https://leetcode.com/problems/subarrays-with-k-different-integers/solutions/523136/JavaC++Python-Sliding-Window/
        retVal = self.atMostDifferent(nums, k) - self.atMostDifferent(nums, k - 1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[1, 2, 1, 2, 3], [1, 2, 1, 3, 4]], [2, 3]):
            # /* Example
            #  *  Input: nums = [1,2,1,2,3], k = 2
            #  *  Output: 7
            #  *
            #  *  Input: nums = [1,2,1,3,4], k = 3
            #  *  Output: 3
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.subarraysWithKDistinct(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
