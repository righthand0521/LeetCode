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
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        retVal = []

        hashTable = defaultdict(int)
        for idx, num in enumerate(nums):
            if num in hashTable:
                retVal = [hashTable[num], idx]
                break
            hashTable[target - num] = idx

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, target in [[[2, 7, 11, 15], 9], [[3, 2, 4], 6], [[3, 3], 6]]:
            # /* Example
            #  *  Input: nums = [2,7,11,15], target = 9
            #  *  Output: [0,1]
            #  *
            #  *  Input: nums = [3,2,4], target = 6
            #  *  Output: [1,2]
            #  *
            #  *  Input: nums = [3,3], target = 6
            #  *  Output: [0,1]
            #  */
            logging.info("Input: nums = %s, target = %s", nums, target)

            retVal = pSolution.twoSum(nums, target)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
