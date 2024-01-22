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
    def findErrorNums(self, nums: List[int]) -> List[int]:
        retVal = [0] * 2

        hashTable = defaultdict(int)
        for num in nums:
            hashTable[num] += 1

        numSize = len(nums)
        for i in range(1, numSize+1):
            if hashTable[i] == 2:
                retVal[0] = i
            elif hashTable[i] == 0:
                retVal[1] = i

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, 2, 2, 4], [1, 1]]:
            # /* Example
            #  *  Input: nums = [1,2,2,4]
            #  *  Output: [2,3]
            #  *
            #  *  Input: nums = [1,1]
            #  *  Output: [1,2]
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.findErrorNums(nums)
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
