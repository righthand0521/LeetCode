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
    def tupleSameProduct(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        pairProductsFrequency = {}
        for firstIndex in range(numsSize):
            for secondIndex in range(firstIndex + 1, numsSize):
                productValue = nums[firstIndex] * nums[secondIndex]
                if productValue in pairProductsFrequency:
                    pairProductsFrequency[productValue] += 1
                else:
                    pairProductsFrequency[productValue] = 1

        for productFrequency in pairProductsFrequency.values():
            pairsOfEqualProduct = ((productFrequency - 1) * productFrequency // 2)
            retVal += 8 * pairsOfEqualProduct  # each pair can form 8 tuples

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[2, 3, 4, 6], [1, 2, 4, 5, 10]]:
            # /* Example
            #  *  Input: nums = [2,3,4,6]
            #  *  Output: 8
            #  *
            #  *  Input: nums = [1,2,4,5,10]
            #  *  Output: 16
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.tupleSameProduct(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
