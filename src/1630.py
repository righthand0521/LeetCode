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
    def checkArithmeticSubarrays(self, nums: List[int], l: List[int], r: List[int]) -> List[bool]:
        retVal = []

        for value in enumerate(zip(l, r)):
            index = value[0]
            left = value[1][0]
            right = value[1][1] + 1

            subarray = sorted(nums[left:right])

            retVal.append(True)
            subarraySize = right - left
            for i in range(1, subarraySize-1):
                if (subarray[i]-subarray[i-1]) != (subarray[i+1]-subarray[i]):
                    retVal[index] = False
                    break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, l, r in zip([[4, 6, 5, 9, 3, 7], [-12, -9, -3, -12, -6, 15, 20, -25, -20, -15, -10]],
                              [[0, 0, 2], [0, 1, 6, 4, 8, 7]],
                              [[2, 3, 5], [4, 4, 9, 7, 9, 10]]):
            # /* Example
            #  *  Input: nums = [4,6,5,9,3,7], l = [0,0,2], r = [2,3,5]
            #  *  Output: [true,false,true]
            #  *
            #  *  Input: nums = [-12,-9,-3,-12,-6,15,20,-25,-20,-15,-10], l = [0,1,6,4,8,7], r = [4,4,9,7,9,10]
            #  *  Output: [false,true,false,false,true,true]
            #  */
            logging.info("Input: nums = %s, l = %s, r = %s", nums, l, r)

            retVal = pSolution.checkArithmeticSubarrays(nums, l, r)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
