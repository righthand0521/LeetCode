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
    def longestSquareStreak(self, nums: List[int]) -> int:
        retVal = 0

        nums.sort()

        hashTable = defaultdict(int)
        for num in nums:
            root = int(num ** 0.5)
            if (root * root == num) and (root in hashTable):
                hashTable[num] = hashTable[root] + 1
            else:
                hashTable[num] = 1

        retVal = max(hashTable.values())
        if retVal == 1:
            retVal = -1  # return -1 if there is no square streak.

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[4, 3, 6, 16, 8, 2], [2, 3, 5, 6, 7]]:
            # /* Example
            #  *  Input: nums = [4,3,6,16,8,2]
            #  *  Output: 3
            #  *
            #  *  Input: nums = [2,3,5,6,7]
            #  *  Output: -1
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.longestSquareStreak(nums)
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
