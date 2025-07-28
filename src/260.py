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
    def singleNumber(self, nums: List[int]) -> List[int]:
        retVal = [0, 0]

        xorSum = 0
        for num in nums:
            xorSum ^= num
        lsb = xorSum & (-xorSum)

        for num in nums:
            idx = 0 if lsb & num == 0 else 1
            retVal[idx] ^= num

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, 2, 1, 3, 2, 5], [-1, 0], [0, 1]]:
            # /* Example
            #  *  Input: nums = [1,2,1,3,2,5]
            #  *  Output: [3,5]
            #  *
            #  *  Input: nums = [-1,0]
            #  *  Output: [-1,0]
            #  *
            #  *  Input: nums = [0,1]
            #  *  Output: [1,0]
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.singleNumber(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
