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
    def findMatrix(self, nums: List[int]) -> List[List[int]]:
        retVal = []

        hashTable = defaultdict(int)
        for num in nums:
            hashTable[num] += 1

        while hashTable:
            row = []
            for i in hashTable:
                row.append(i)
                hashTable[i] -= 1
            retVal.append(row)

            for i in row:
                if hashTable[i] == 0:
                    hashTable.pop(i)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, 3, 4, 1, 2, 3, 1], [1, 2, 3, 4]]:
            # /* Example
            #  *  Input: nums = [1,3,4,1,2,3,1]
            #  *  Output: [[1,3,4,2],[1,3],[1]]
            #  *
            #  *  Input: nums = [1,2,3,4]
            #  *  Output: [[4,3,2,1]]
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.findMatrix(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
