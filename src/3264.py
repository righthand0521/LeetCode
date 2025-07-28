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
    def getFinalState(self, nums: List[int], k: int, multiplier: int) -> List[int]:
        retVal = nums

        minHeap = []
        for idx, num in enumerate(retVal):
            minHeap.append((num, idx))
        heapify(minHeap)

        for _ in range(k):
            num, idx = heappop(minHeap)
            retVal[idx] *= multiplier
            heappush(minHeap, (retVal[idx], idx))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k, multiplier in zip([[2, 1, 3, 5, 6], [1, 2]], [5, 3], [2, 4]):
            # /* Example
            #  *  Input: nums = [2,1,3,5,6], k = 5, multiplier = 2
            #  *  Output: [8,4,6,5,6]
            #  *
            #  *  Input: nums = [1,2], k = 3, multiplier = 4
            #  *  Output: [16,8]
            #  */
            logging.info("Input: nums = %s, k = %s, multiplier = %s", nums, k, multiplier)

            retVal = pSolution.getFinalState(nums, k, multiplier)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
