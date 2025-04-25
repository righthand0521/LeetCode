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
    def countInterestingSubarrays(self, nums: List[int], modulo: int, k: int) -> int:
        retVal = 0

        hashTable = Counter([0])

        prefix = 0
        numsSize = len(nums)
        for i in range(numsSize):
            if nums[i] % modulo == k:
                prefix += 1
            retVal += hashTable[(prefix - k + modulo) % modulo]
            hashTable[prefix % modulo] += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, modulo, k in zip([[3, 2, 4], [3, 1, 9, 6]], [2, 3], [1, 0]):
            # /* Example
            #  *  Input: nums = [3,2,4], modulo = 2, k = 1
            #  *  Output: 3
            #  *
            #  *  Input: nums = [3,1,9,6], modulo = 3, k = 0
            #  *  Output: 2
            #  */
            logging.info("Input: nums = %s, modulo = %s, k = %s", nums, modulo, k)

            retVal = pSolution.countInterestingSubarrays(nums, modulo, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
