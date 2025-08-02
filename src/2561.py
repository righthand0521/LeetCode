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
    def minCost(self, basket1: List[int], basket2: List[int]) -> int:
        retVal = -1

        frequency = Counter()

        minValue = float("inf")
        for b1 in basket1:
            frequency[b1] += 1
            minValue = min(minValue, b1)
        for b2 in basket2:
            frequency[b2] -= 1
            minValue = min(minValue, b2)

        merge = []
        for key, value in frequency.items():
            if value % 2 != 0:
                return retVal
            merge.extend([key] * (abs(value) // 2))

        if not merge:
            retVal = 0
            return retVal
        merge.sort()

        retVal = sum(min(2 * minValue, x) for x in merge[: len(merge) // 2])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for basket1, basket2 in [[[4, 2, 2, 2], [1, 4, 1, 2]], [[2, 3, 4, 1], [3, 2, 5, 1]]]:
            # /* Example
            #  *  Input: basket1 = [4,2,2,2], basket2 = [1,4,1,2]
            #  *  Output: 1
            #  *
            #  *  Input: basket1 = [2,3,4,1], basket2 = [3,2,5,1]
            #  *  Output: -1
            #  */
            logging.info("Input: basket1 = %s, basket2 = %s", basket1, basket2)

            retVal = pSolution.minCost(basket1, basket2)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
