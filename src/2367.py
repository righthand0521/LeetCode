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
    def arithmeticTriplets(self, nums: List[int], diff: int) -> int:
        retVal = 0

        hashTable = defaultdict(bool)
        for num in nums:
            hashTable[num] = True
        for num in nums:
            if (num+diff in hashTable) and (num+diff+diff in hashTable):
                retVal += 1

        # for num in nums:
        #     if (num+diff in nums) and (num+diff+diff in nums):
        #         retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, diff in zip([[0, 1, 4, 6, 7, 10], [4, 5, 6, 7, 8, 9]], [3, 2]):
            # /* Example
            #  *  Input: nums = [0,1,4,6,7,10], diff = 3
            #  *  Output: 2
            #  *
            #  *  Input: nums = [4,5,6,7,8,9], diff = 2
            #  *  Output: 2
            #  */
            logging.info("Input: nums = %s, diff = %s", nums, diff)

            retVal = pSolution.arithmeticTriplets(nums, diff)
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
