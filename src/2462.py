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
    def totalCost(self, costs: List[int], k: int, candidates: int) -> int:
        retVal = 0

        leftHeap = costs[:candidates]
        heapify(leftHeap)
        rightHeap = costs[max(candidates, len(costs) - candidates):]
        heapify(rightHeap)

        left = candidates
        right = len(costs) - 1 - candidates
        for _ in range(k):
            if (not rightHeap) or ((leftHeap) and (leftHeap[0] <= rightHeap[0])):
                retVal += heappop(leftHeap)
                if left <= right:
                    heappush(leftHeap, costs[left])
                    left += 1
            else:
                retVal += heappop(rightHeap)
                if left <= right:
                    heappush(rightHeap, costs[right])
                    right -= 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for costs, k, candidates in zip([[17, 12, 10, 2, 7, 2, 11, 20, 8], [1, 2, 4, 1]], [3, 3], [4, 3]):
            # /* Example
            #  *  Input: costs = [17,12,10,2,7,2,11,20,8], k = 3, candidates = 4
            #  *  Output: 11
            #  *
            #  *  Input: costs = [1,2,4,1], k = 3, candidates = 3
            #  *  Output: 4
            #  */
            logging.info(
                "Input: costs = %s, k = %s, candidates = %s", costs, k, candidates)

            retVal = pSolution.totalCost(costs, k, candidates)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
