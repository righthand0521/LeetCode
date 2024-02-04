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
    def longestConsecutive(self, nums: List[int]) -> int:
        retVal = 0

        hashTable = defaultdict(int)
        for num in nums:
            if num in hashTable:
                continue

            left = 0
            if (num - 1) in hashTable:
                left = hashTable[num - 1]

            right = 0
            if (num + 1) in hashTable:
                right = hashTable[num + 1]

            length = left + right + 1
            hashTable[num] = 1
            hashTable[num - left] = length
            hashTable[num + right] = length

            retVal = max(retVal, length)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[100, 4, 200, 1, 3, 2], [0, 3, 7, 2, 5, 8, 4, 6, 0, 1]]:
            # /* Example
            #  *  Input: nums = [100,4,200,1,3,2]
            #  *  Output: 4
            #  *
            #  *  Input: nums = [0,3,7,2,5,8,4,6,0,1]
            #  *  Output: 9
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.longestConsecutive(nums)
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
