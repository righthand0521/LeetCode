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
    def getSneakyNumbers(self, nums: List[int]) -> List[int]:
        retVal = []

        hashTable = defaultdict(int)
        for num in nums:
            hashTable[num] += 1
            if hashTable[num] == 2:
                retVal.append(num)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[0, 1, 1, 0], [0, 3, 2, 1, 3, 2], [7, 1, 5, 4, 3, 4, 6, 0, 9, 5, 8, 2]]:
            # /* Example
            #  *  Input: nums = [0,1,1,0]
            #  *  Output: [0,1]
            #  *
            #  *  Input: nums = [0,3,2,1,3,2]
            #  *  Output: [2,3]
            #  *
            #  *  Input: nums = [7,1,5,4,3,4,6,0,9,5,8,2]
            #  *  Output: [4,5]
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.getSneakyNumbers(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
