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
    def maxProduct(self, nums: List[int]) -> int:
        retVal = float("-inf")

        maxValue = 1
        minValue = 1
        for num in nums:
            # /* Dynamic Programming
            # *  keep max = MAX(max, nums[i])
            # *  keep min = MIN(min, nums[i]) because -10 <= nums[i] <= 10
            # *  swap max and min if nums[i] < 0
            # *
            # *  Example
            # *   nums[] = {2, 3, -2, 4}
            # *   nums[0]=2: keep max=2, min=2; retVal=2.
            # *   nums[1]=3: keep max=6, min=3; retVal=6.
            # *   nums[2]=-2: swap max=3, min=6; keep max=-2, min=-12; retVal=6.
            # *   nums[3]=4: keep max=4, min=-48; retVal=6.
            # */
            if num < 0:
                tmp = maxValue
                maxValue = minValue
                minValue = tmp
            maxValue = max(num, (maxValue * num))
            minValue = min(num, (minValue * num))
            retVal = max(retVal, maxValue)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[2, 3, -2, 4], [-2, 0, -1], [0, 10, 10, 10, 10, 10, 10, 10, 10, 10, -10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 0]]:
            # /* Example
            #  *  Input: nums = [2,3,-2,4]
            #  *  Output: 6
            #  *
            #  *  Input: nums = [-2,0,-1]
            #  *  Output: 0
            #  *
            #  *  Input: nums = [0,10,10,10,10,10,10,10,10,10,-10,10,10,10,10,10,10,10,10,10,0]
            #  *  Output: 1000000000]
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.maxProduct(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
