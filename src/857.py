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
    def mincostToHireWorkers(self, quality: List[int], wage: List[int], k: int) -> float:
        retVal = float("inf")

        qualitySize = len(quality)

        wage_to_quality_ratio = []
        for i in range(qualitySize):
            wage_to_quality_ratio.append((wage[i] / quality[i], quality[i]))
        wage_to_quality_ratio.sort(key=lambda x: x[0])

        highest_quality_workers = []
        current_total_quality = 0
        for i in range(qualitySize):
            heappush(highest_quality_workers, -wage_to_quality_ratio[i][1])
            current_total_quality += wage_to_quality_ratio[i][1]

            if len(highest_quality_workers) > k:
                current_total_quality += heappop(highest_quality_workers)

            if len(highest_quality_workers) == k:
                retVal = min(retVal, current_total_quality * wage_to_quality_ratio[i][0])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for quality, wage, k in zip([[10, 20, 5], [3, 1, 10, 10, 1]], [[70, 50, 30], [4, 8, 2, 2, 7]], [2, 3]):
            # /* Example
            #  *  Input: quality = [10,20,5], wage = [70,50,30], k = 2
            #  *  Output: 105.00000
            #  *
            #  *  Input: quality = [3,1,10,10,1], wage = [4,8,2,2,7], k = 3
            #  *  Output: 30.66667
            #  */
            logging.info("Input: quality = %s, wage = %s, k = %s", quality, wage, k)

            retVal = pSolution.mincostToHireWorkers(quality, wage, k)
            logging.info("Output: %.5f", retVal)

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
