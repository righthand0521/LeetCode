import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop
from math import log10, ceil


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
    def poorPigs(self, buckets: int, minutesToDie: int, minutesToTest: int) -> int:
        retVal = 0

        # https: // leetcode.cn/problems/poor-pigs/solutions/15770/hua-jie-suan-fa-458-ke-lian-de-xiao-zhu-by-guanpen/
        #   pow(base, answer) ≥ buckets
        #   = > answer ≥ log(buckets) / log(base)
        #   = > answer = ceil(log(buckets) / log(base))
        base = minutesToTest / minutesToDie + 1
        retVal = ceil(log10(buckets) / log10(base))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for buckets, minutesToDie, minutesToTest in zip([4, 4], [15, 15], [15, 30]):
            # /* Example
            #  *  Input: buckets = 4, minutesToDie = 15, minutesToTest = 15
            #  *  Output: 2
            #  *
            #  *  Input: buckets = 4, minutesToDie = 15, minutesToTest = 30
            #  *  Output: 2
            #  */
            logging.info("Input: buckets = %s, minutesToDie = %s, minutesToTest = %s",
                         buckets, minutesToDie, minutesToTest)

            retVal = pSolution.poorPigs(buckets, minutesToDie, minutesToTest)
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
