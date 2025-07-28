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
    def containsDuplicate(self, nums: List[int]) -> bool:
        retVal = False

        hashTable = defaultdict(int)
        for num in nums:
            if num in hashTable:
                retVal = True
                break
            hashTable[num] = 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, 2, 3, 1], [1, 2, 3, 4], [1, 1, 1, 3, 3, 4, 3, 2, 4, 2]]:
            # /* Example:
            #  *  Input: nums = [1,2,3,1]
            #  *  Output: true
            #  *
            #  *  Input: nums = [1,2,3,4]
            #  *  Output: false
            #  *
            #  *  Input: nums = [1,1,1,3,3,4,3,2,4,2]
            #  *  Output: true
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.containsDuplicate(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
