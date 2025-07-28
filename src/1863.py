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
    def subsetXORSum(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        # Capture each bit that is set in any of the elements
        for num in nums:
            retVal |= num

        # Multiply by the number of subset XOR totals that will have each bit set
        retVal = retVal << (numsSize - 1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, 3], [5, 1, 6], [3, 4, 5, 6, 7, 8], [2, 4, 4]]:
            # /* Example
            #  *  Input: nums = [1,3]
            #  *  Output: 6
            #  *
            #  *  Input: nums = [5,1,6]
            #  *  Output: 28
            #  *
            #  *  Input: nums = [3,4,5,6,7,8]
            #  *  Output: 480
            #  *
            #  *  Input: nums = [2,4,4]
            #  *  Output: 24
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.subsetXORSum(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
