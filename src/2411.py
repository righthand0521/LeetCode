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
    def __init__(self) -> None:
        self.maxBit = 31  # 0 <= nums[i] <= 10^9

    def smallestSubarrays(self, nums: List[int]) -> List[int]:
        retVal = []

        numSize = len(nums)

        retVal = [0] * numSize
        pos = [-1] * self.maxBit
        for i in range(numSize - 1, -1, -1):
            j = i
            for bit in range(self.maxBit):
                if (nums[i] & (1 << bit)) == 0:
                    if pos[bit] != -1:
                        j = max(j, pos[bit])
                else:
                    pos[bit] = i
            retVal[i] = j - i + 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, 0, 2, 1, 3], [1, 2]]:
            # /* Example
            #  *  Input: nums = [1,0,2,1,3]
            #  *  Output: [3,3,2,2,1]
            #  *
            #  *  Input: nums = [1,2]
            #  *  Output: [2,1]
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.smallestSubarrays(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
