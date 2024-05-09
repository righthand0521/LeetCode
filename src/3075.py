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
    def maximumHappinessSum(self, happiness: List[int], k: int) -> int:
        retVal = 0

        happiness.sort(reverse=True)
        for i in range(k):
            happy = happiness[i] - i
            if happy <= 0:
                break
            retVal += happy

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for happiness, k in zip([[1, 2, 3], [1, 1, 1, 1], [2, 3, 4, 5]], [2, 2, 1]):
            # /* Example
            #  *  Input: happiness = [1,2,3], k = 2
            #  *  Output: 4
            #  *
            #  *  Input: happiness = [1,1,1,1], k = 2
            #  *  Output: 1
            #  *
            #  *  Input: happiness = [2,3,4,5], k = 1
            #  *  Output: 5
            #  */
            logging.info("Input: happiness = %s, k = %s", happiness, k)

            retVal = pSolution.maximumHappinessSum(happiness, k)
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
