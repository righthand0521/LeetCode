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
    def intersectionSizeTwo(self, intervals: List[List[int]]) -> int:
        retVal = 0

        intervals.sort(key=lambda x: (x[0], -x[1]))

        intervalsSize = len(intervals)
        vals = [[] for _ in range(intervalsSize)]
        for i in range(intervalsSize - 1, -1, -1):
            j = intervals[i][0]

            valsSize = len(vals[i])
            for k in range(valsSize, 2):
                retVal += 1

                for p in range(i - 1, -1, -1):
                    if intervals[p][1] < j:
                        break
                    vals[p].append(j)

                j += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for intervals in [[[1, 3], [3, 7], [8, 9]], [[1, 3], [1, 4], [2, 5], [3, 5]], [[1, 2], [2, 3], [2, 4], [4, 5]]]:
            # /* Example
            #  *  Input: intervals = [[1,3],[3,7],[8,9]]
            #  *  Output: 5
            #  *
            #  *  Input: intervals = [[1,3],[1,4],[2,5],[3,5]]
            #  *  Output: 3
            #  *
            #  *  Input: intervals = [[1,2],[2,3],[2,4],[4,5]]
            #  *  Output: 5
            #  */
            logging.info("Input: intervals = %s", intervals)

            retVal = pSolution.intersectionSizeTwo(intervals)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
