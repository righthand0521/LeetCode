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
    def subarraySum(self, nums: List[int], k: int) -> int:
        retVal = 0

        prefixSumMap = defaultdict(int)
        prefixSumMap[0] = 1

        prefixSum = 0
        for num in nums:
            prefixSum += num
            if (prefixSum - k) in prefixSumMap:
                retVal += prefixSumMap[prefixSum - k]
            prefixSumMap[prefixSum] += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[1, 1, 1], [1, 2, 3]], [2, 3]):
            # /* Example
            #  *  Input: nums = [1,1,1], k = 2
            #  *  Output: 2
            #  *
            #  *  Input: nums = [1,2,3], k = 3
            #  *  Output: 2
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.subarraySum(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
