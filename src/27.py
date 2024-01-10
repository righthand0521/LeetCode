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
    def removeElement(self, nums: List[int], val: int) -> int:
        retVal = 0

        numsSize = len(nums)
        for i in range(numsSize):
            if nums[i] != val:
                nums[retVal] = nums[i]
                retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, val in zip([[3, 2, 2, 3], [0, 1, 2, 2, 3, 0, 4, 2]], [3, 2]):
            # /* Example
            #  *  Input: nums = [3,2,2,3], val = 3
            #  *  Output: 2, nums = [2,2,_,_]
            #  *
            #  *  Input: nums = [0,1,2,2,3,0,4,2], val = 2
            #  *  Output: 5, nums = [0,1,4,0,3,_,_,_]
            #  */
            logging.info("Input: nums = %s, val = %s", nums, val)

            retVal = pSolution.removeElement(nums, val)
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
