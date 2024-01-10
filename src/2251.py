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
    def fullBloomFlowers(self, flowers: List[List[int]], people: List[int]) -> List[int]:
        retVal = []

        starts = []
        ends = []
        for start, end in flowers:
            starts.append(start)
            ends.append(end + 1)
        starts.sort()
        ends.sort()

        for p in people:
            i = bisect_right(starts, p)
            j = bisect_right(ends, p)
            retVal.append(i - j)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for flowers, poeple in zip([[[1, 6], [3, 7], [9, 12], [4, 13]], [[1, 10], [3, 3]]], [[2, 3, 7, 11], [3, 3, 2]]):
            # /* Example
            #  *  Input: flowers = [[1,6],[3,7],[9,12],[4,13]], poeple = [2,3,7,11]
            #  *  Output: [1,2,2,2]
            #  *
            #  *  Input: flowers = [[1,10],[3,3]], poeple = [3,3,2]
            #  *  Output: [2,2,1]
            #  */
            logging.info("Input: flowers = %s, poeple = %s", flowers, poeple)

            retVal = pSolution.fullBloomFlowers(flowers, poeple)
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
