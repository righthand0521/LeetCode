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
    def __init__(self) -> None:
        self.MODULO = 10 ** 9 + 7

    def countNicePairs(self, nums: List[int]) -> int:
        retVal = 0

        # /* nums[i] + rev(nums[j]) == nums[j] + rev(nums[i])
        #  * =>  nums[i] - rev(nums[i]) == nums[j] - rev(nums[j])
        #  */
        hashTable = defaultdict(int)
        for num in nums:
            index = num - int(str(num)[::-1])
            retVal += hashTable[index]
            retVal %= self.MODULO
            hashTable[index] += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[42, 11, 1, 97], [13, 10, 35, 24, 76]]:
            # /* Example
            #  *  Input: nums = [42,11,1,97]
            #  *  Output: 2
            #  *
            #  *  Input: nums = [13,10,35,24,76]
            #  *  Output: 4
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.countNicePairs(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
