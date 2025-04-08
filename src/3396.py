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
    def minimumOperations(self, nums: List[int]) -> int:
        retVal = 0

        hashTable = [0] * 128  # 1 <= nums.length <= 100

        numsSize = len(nums)
        for i in range(numsSize-1, -1, -1):
            if hashTable[nums[i]] == 1:
                retVal = i // 3 + 1
                break
            hashTable[nums[i]] = 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, 2, 3, 4, 2, 3, 3, 5, 7], [4, 5, 6, 4, 4], [6, 7, 8, 9]]:
            # /* Example
            #  *  Input: nums = [1,2,3,4,2,3,3,5,7]
            #  *  Output: 2
            #  *
            #  *  Input: nums = [4,5,6,4,4]
            #  *  Output: 2
            #  *
            #  *  Input: nums = [6,7,8,9]
            #  *  Output: 0
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.minimumOperations(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
