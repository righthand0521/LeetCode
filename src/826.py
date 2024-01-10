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
    def maxProfitAssignment(self, difficulty: List[int], profit: List[int], worker: List[int]) -> int:
        retVal = 0

        job = sorted(zip(difficulty, profit))
        jobSize = len(job)
        jobIdx = 0

        maxProfit = 0
        worker.sort()
        for pWorker in worker:
            while (jobIdx < jobSize) and (pWorker >= job[jobIdx][0]):
                maxProfit = max(maxProfit, job[jobIdx][1])
                jobIdx += 1

            retVal += maxProfit

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for difficulty, profit, worker in zip([[2, 4, 6, 8, 10], [85, 47, 57]],
                                              [[10, 20, 30, 40, 50], [24, 66, 99]],
                                              [[4, 5, 6, 7], [40, 25, 25]]):
            # /* Example
            #  *  Input: difficulty = [2,4,6,8,10], profit = [10,20,30,40,50], worker = [4,5,6,7]
            #  *  Output: 100
            #  *
            #  *  Input: difficulty = [85,47,57], profit = [24,66,99], worker = [40,25,25]
            #  *  Output: 0
            #  */
            logging.info(
                "Input: difficulty = %s, profit = %s, worker = %s", difficulty, profit, worker)

            retVal = pSolution.maxProfitAssignment(difficulty, profit, worker)
            logging.info("Output: %d", retVal)

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
