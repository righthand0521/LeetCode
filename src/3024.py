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
    def __init__(self) -> None:
        self.none = "none"
        self.equilateral = "equilateral"
        self.isosceles = "isosceles"
        self.scalene = "scalene"

    def triangleType(self, nums: List[int]) -> str:
        retVal = ""

        nums.sort()
        if nums[0] + nums[1] <= nums[2]:
            retVal = self.none
        elif nums[0] == nums[2]:
            retVal = self.equilateral
        elif (nums[0] == nums[1]) or (nums[1] == nums[2]):
            retVal = self.isosceles
        else:
            retVal = self.scalene

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[3, 3, 3], [3, 4, 5]]:
            # /* Example
            #  *  Input: nums = [3,3,3]
            #  *  Output: "equilateral"
            #  *
            #  *  Input: nums = [3,4,5]
            #  *  Output: "scalene"
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.triangleType(nums)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
