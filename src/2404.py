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
    def mostFrequentEven(self, nums: List[int]) -> int:
        retVal = -1

        hashTable = Counter(nums)
        sortHashTableKey = sorted(hashTable, key=lambda i: (-hashTable[i], i))
        for key in sortHashTableKey:
            if key % 2 == 0:
                retVal = key
                break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[0, 1, 2, 2, 4, 4, 1], [4, 4, 4, 9, 2, 4], [29, 47, 21, 41, 13, 37, 25, 7]]:
            # /* Example
            #  *  Input: nums = [0,1,2,2,4,4,1]
            #  *  Output: 2
            #  *
            #  *  Input: nums = [4,4,4,9,2,4]
            #  *  Output: 4
            #  *
            #  *  Input: nums = [29,47,21,41,13,37,25,7]
            #  *  Output: -1
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.mostFrequentEven(nums)
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
