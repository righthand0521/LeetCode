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
    def removeDuplicates(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        if numsSize < 2:
            retVal = numsSize
            return retVal

        count = 0
        for i in range(1, numsSize):
            if nums[retVal] != nums[i]:
                count = 0
            else:
                count += 1

            if count < 2:
                retVal += 1
                nums[retVal] = nums[i]
        retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, 1, 1, 2, 2, 3], [0, 0, 1, 1, 1, 1, 2, 3, 3]]:
            # /* Example
            #  *  Input: nums = [1,1,1,2,2,3]
            #  *  Output: 5, nums = [1,1,2,2,3,_]
            #  *
            #  *  Input: nums = [0,0,1,1,1,1,2,3,3]
            #  *  Output: 7, nums = [0,0,1,1,2,3,3,_,_]
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.removeDuplicates(nums)
            logging.info("Output: %s, nums = %s", retVal, nums[:retVal])

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
