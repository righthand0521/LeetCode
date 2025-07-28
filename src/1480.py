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
    def runningSum(self, nums: List[int]) -> List[int]:
        retVal = []

        retVal.append(nums[0])
        for i in range(1, len(nums)):
            retVal.append(retVal[i-1] + nums[i])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, 2, 3, 4], [1, 1, 1, 1, 1], [3, 1, 2, 10, 1]]:
            # /* Example
            #  *  Input: nums = [1,2,3,4]
            #  *  Output: [1,3,6,10]
            #  *
            #  *  Input: nums = [1,1,1,1,1]
            #  *  Output: [1,2,3,4,5]
            #  *
            #  *  Input: nums = [3,1,2,10,1]
            #  *  Output: [3,4,6,16,17]
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.runningSum(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
