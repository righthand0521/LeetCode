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
    def maxChunksToSorted(self, arr: List[int]) -> int:
        retVal = 0

        arrSize = len(arr)
        maxElement = 0
        for i in range(arrSize):
            maxElement = max(maxElement, arr[i])
            # All values in range [0, i] belong to the prefix arr[0:i]; a chunk can be formed
            if maxElement == i:
                retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr in [[4, 3, 2, 1, 0], [1, 0, 2, 3, 4]]:
            # /* Example
            #  *  Input: arr = [4,3,2,1,0]
            #  *  Output: 1
            #  *
            #  *  Input: arr = [1,0,2,3,4]
            #  *  Output: 4
            #  */
            logging.info("Input: arr = %s", arr)

            retVal = pSolution.maxChunksToSorted(arr)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
