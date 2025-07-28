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
    def jump(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        maxPosition = 0
        end = 0
        for i in range(numsSize-1):
            # find maximum jumping length
            maxPosition = max(maxPosition, nums[i] + i)

            # reach end boundary need to  update end boundary and add steps
            if i == end:
                end = maxPosition
                retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[2, 3, 1, 1, 4], [2, 3, 0, 1, 4]]:
            # /* Example
            #  *  Input: nums = [2,3,1,1,4]
            #  *  Output: 2
            #  *
            #  *  Input: nums = [2,3,0,1,4]
            #  *  Output: 2
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.jump(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
