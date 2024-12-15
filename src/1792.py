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
    def calculateGain(self, passes, totalStudents) -> float:
        retVal = 0

        retVal = (passes + 1) / (totalStudents + 1) - passes / totalStudents

        return retVal

    def maxAverageRatio(self, classes: List[List[int]], extraStudents: int) -> float:
        retVal = 0

        # Max heap to store (-gain, passes, totalStudents)
        maxHeap = []
        for passes, totalStudents in classes:
            gain = self.calculateGain(passes, totalStudents)
            heappush(maxHeap, (-gain, passes, totalStudents))

        # Distribute extra students
        for _ in range(extraStudents):
            _, passes, totalStudents = heappop(maxHeap)
            gain = self.calculateGain(passes + 1, totalStudents + 1)
            heappush(maxHeap, (-gain, passes + 1, totalStudents + 1,))

        # Calculate the final average pass ratio
        totalPassRatio = 0
        while maxHeap:
            _, passes, totalStudents = heappop(maxHeap)
            totalPassRatio += (passes / totalStudents)
        retVal = totalPassRatio / len(classes)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for classes, extraStudents in zip([[[1, 2], [3, 5], [2, 2]], [[2, 4], [3, 9], [4, 5], [2, 10]]], [2, 4]):
            # /* Example
            #  *  Input: classes = [[1,2],[3,5],[2,2]], extraStudents = 2
            #  *  Output: 0.78333
            #  *
            #  *  Input: classes = [[2,4],[3,9],[4,5],[2,10]], extraStudents = 4
            #  *  Output: 0.53485
            #  */
            logging.info("Input: classes = %s, extraStudents = %s", classes, extraStudents)

            retVal = pSolution.maxAverageRatio(classes, extraStudents)
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
