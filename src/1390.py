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
    def sumFourDivisors(self, nums: List[int]) -> int:
        retVal = 0

        for num in nums:
            factorCount = 0
            factorSum = 0

            i = 1
            while i * i <= num:
                if num % i == 0:
                    factorCount += 1
                    factorSum += i
                    if i * i != num:
                        factorCount += 1
                        factorSum += (num // i)
                i += 1

            if factorCount == 4:
                retVal += factorSum

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[21, 4, 7], [21, 21], [1, 2, 3, 4, 5]]:
            # /* Example
            #  *  Input: nums = [21,4,7]
            #  *  Output: 32
            #  *
            #  *  Input: nums = [21,21]
            #  *  Output: 64
            #  *
            #  *  Input: nums = [1,2,3,4,5]
            #  *  Output: 0
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.sumFourDivisors(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
