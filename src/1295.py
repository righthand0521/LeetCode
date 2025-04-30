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
    def findNumbers(self, nums: List[int]) -> int:
        retVal = 0

        for num in nums:
            count = 0
            while num > 0:
                count += 1
                num //= 10
            if count % 2 == 0:
                retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[12, 345, 2, 6, 7896], [555, 901, 482, 1771]]:
            # /* Example
            #  *  Input: nums = [12,345,2,6,7896]
            #  *  Output: 2
            #  *
            #  *  Input: nums = [555,901,482,1771]
            #  *  Output: 1
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.findNumbers(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
