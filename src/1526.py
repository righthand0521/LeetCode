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
    def minNumberOperations(self, target: List[int]) -> int:
        retVal = 0

        targetSize = len(target)
        retVal = target[0]
        for i in range(1, targetSize):
            retVal += max(target[i] - target[i - 1], 0)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for target in [[1, 1, 2], [0, 0, 1, 1, 1, 2, 2, 3, 3, 4]]:
            # /* Example
            #  *  Input: target = [1,2,3,2,1]
            #  *  Output: 3
            #  *
            #  *  Input: target = [3,1,1,2]
            #  *  Output: 4
            #  *
            #  *  Input: target = [3,1,5,4,2]
            #  *  Output: 7
            #  */
            logging.info("Input: target = %s", target)

            retVal = pSolution.minNumberOperations(target)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
