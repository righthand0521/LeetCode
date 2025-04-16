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
    def countGood(self, nums: List[int], k: int) -> int:
        retVal = 0

        hashTable = Counter()

        numsSize = len(nums)
        same = 0
        right = -1
        for left in range(numsSize):
            while (same < k) and (right + 1 < numsSize):
                right += 1
                same += hashTable[nums[right]]
                hashTable[nums[right]] += 1

            if same >= k:
                retVal += (numsSize - right)

            hashTable[nums[left]] -= 1
            same -= hashTable[nums[left]]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[1, 1, 1, 1, 1], [3, 1, 4, 3, 2, 2, 4]], [10, 2]):
            # /* Example
            #  *  Input: nums = [1,1,1,1,1], k = 10
            #  *  Output: 1
            #  *
            #  *  Input: nums = [3,1,4,3,2,2,4], k = 2
            #  *  Output: 4
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.countGood(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
