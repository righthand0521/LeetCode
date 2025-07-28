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
    def groupThePeople(self, groupSizes: List[int]) -> List[List[int]]:
        retVal = []

        hashTable = defaultdict(list)

        groupSizesSize = len(groupSizes)
        for i in range(groupSizesSize):
            hashTable[groupSizes[i]].append(i)
        hashTable = sorted(hashTable.items())

        for key, value in hashTable:
            valueSize = len(value)
            for i in range(valueSize//key):
                retVal.append(value[key*i:key*(i+1)])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for groupSizes in [[3, 3, 3, 3, 3, 1, 3], [2, 1, 3, 3, 3, 2]]:
            # /* Example
            #  *  Input: groupSizes = [3,3,3,3,3,1,3]
            #  *  Output: [[5],[0,1,2],[3,4,6]]
            #  *
            #  *  Input: groupSizes = [2,1,3,3,3,2]
            #  *  Output: [[1],[0,5],[2,3,4]]
            #  */
            logging.info("Input: groupSizes = %s", groupSizes)

            retVal = pSolution.groupThePeople(groupSizes)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
