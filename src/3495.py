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
    def get(self, num: int) -> int:
        retVal = 0

        i = 1
        base = 1
        while base <= num:
            retVal += ((i + 1) // 2) * (min(base * 2 - 1, num) - base + 1)
            i += 1
            base *= 2

        return retVal

    def minOperations(self, queries: List[List[int]]) -> int:
        retVal = 0

        for query in queries:
            retVal += (self.get(query[1]) - self.get(query[0] - 1) + 1) // 2

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for queries in [[[1, 2], [2, 4]], [[2, 6]]]:
            # /* Example
            #  *  Input: queries = [[1,2],[2,4]]
            #  *  Output: 3
            #  *
            #  *  Input: queries = [[2,6]]
            #  *  Output: 4
            #  */
            logging.info("Input: queries = %s", queries)

            retVal = pSolution.minOperations(queries)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
