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
    def maximumValueSum(self, nums: List[int], k: int, edges: List[List[int]]) -> int:
        retVal = 0

        sumVal = 0
        count = 0
        positiveMinimum = 1 << 30
        negativeMaximum = -1 * (1 << 30)
        for nodeValue in nums:
            operatedNodeValue = nodeValue ^ k
            sumVal += nodeValue
            netChange = operatedNodeValue - nodeValue
            if netChange > 0:
                positiveMinimum = min(positiveMinimum, netChange)
                sumVal += netChange
                count += 1
            else:
                negativeMaximum = max(negativeMaximum, netChange)

        # If the number of positive netChange values is even, return the sum.
        # Otherwise return the maximum of both discussed cases.
        if count % 2 == 0:
            retVal = sumVal
        else:
            retVal = max(sumVal - positiveMinimum, sumVal + negativeMaximum)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k, edges in zip([[1, 2, 1], [2, 3], [7, 7, 7, 7, 7, 7]],
                                  [3, 7, 3],
                                  [[[0, 1], [0, 2]], [[0, 1]], [[0, 1], [0, 2], [0, 3], [0, 4], [0, 5]]]):
            # /* Example
            #  *  Input: nums = [1,2,1], k = 3, edges = [[0,1],[0,2]]
            #  *  Output: 6
            #  *
            #  *  Input: nums = [2,3], k = 7, edges = [[0,1]]
            #  *  Output: 9
            #  *
            #  *  Input: nums = [7,7,7,7,7,7], k = 3, edges = [[0,1],[0,2],[0,3],[0,4],[0,5]]
            #  *  Output: 42
            #  */
            logging.info("Input: nums = %s, k = %s, edges = %s", nums, k, edges)

            retVal = pSolution.maximumValueSum(nums, k, edges)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
