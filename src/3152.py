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
    def isArraySpecial(self, nums: List[int], queries: List[List[int]]) -> List[bool]:
        retVal = []

        numsSize = len(nums)
        prefix = [0] * numsSize
        for i in range(1, numsSize):
            if nums[i] % 2 == nums[i - 1] % 2:
                prefix[i] = prefix[i - 1] + 1  # new violative index found
            else:
                prefix[i] = prefix[i - 1]

        for start, end in queries:
            value = (prefix[end] - prefix[start] == 0)
            retVal.append(value)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, queries in zip([[3, 4, 1, 2, 6], [4, 3, 1, 6]], [[[0, 4]], [[0, 2], [2, 3]]]):
            # /* Example
            #  *  Input: nums = [3,4,1,2,6], queries = [[0,4]]
            #  *  Output: [false]
            #  *
            #  *  Input: nums = [4,3,1,6], queries = [[0,2],[2,3]]
            #  *  Output: [false,true]
            #  */
            logging.info("Input: nums = %s, queries = %s", nums, queries)

            retVal = pSolution.isArraySpecial(nums, queries)
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
