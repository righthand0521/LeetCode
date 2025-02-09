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
    def countBadPairs(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        diffCount = {}
        for pos in range(numsSize):
            diff = pos - nums[pos]
            goodPairsCount = diffCount.get(diff, 0)  # Count of previous positions with same difference
            retVal += pos - goodPairsCount  # Total possible pairs minus good pairs = bad pairs
            diffCount[diff] = goodPairsCount + 1  # Update count of positions with this difference

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[4, 1, 3, 3], [1, 2, 3, 4, 5]]:
            # /* Example
            #  *  Input: nums = [4,1,3,3]
            #  *  Output: 5
            #  *
            #  *  Input: nums = [1,2,3,4,5]
            #  *  Output: 0
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.countBadPairs(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
