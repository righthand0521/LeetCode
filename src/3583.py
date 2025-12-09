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
    def __init__(self) -> None:
        self.MODULO = 10 ** 9 + 7

    def specialTriplets(self, nums: List[int]) -> int:
        retVal = 0

        numCnt = {}
        for v in nums:
            numCnt[v] = numCnt.get(v, 0) + 1

        numPartialCnt = {}
        for v in nums:
            target = v * 2
            lCnt = numPartialCnt.get(target, 0)
            numPartialCnt[v] = numPartialCnt.get(v, 0) + 1

            rCnt = numCnt.get(target, 0) - numPartialCnt.get(target, 0)
            retVal = (retVal + lCnt * rCnt) % self.MODULO

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[6, 3, 6], [0, 1, 0, 0], [8, 4, 2, 8, 4]]:
            # /* Example
            #  *  Input: nums = [6,3,6]
            #  *  Output: 1
            #  *
            #  *  Input: nums = [0,1,0,0]
            #  *  Output: 1
            #  *
            #  *  Input: nums = [8,4,2,8,4]
            #  *  Output: 2
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.specialTriplets(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
