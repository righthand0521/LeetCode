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
    def binarySearch(self, items, targetPrice) -> int:
        retVal = 0

        left = 0
        right = len(items) - 1
        while left <= right:
            middle = (left + right) // 2
            if items[middle][0] > targetPrice:
                right = middle - 1
            else:
                retVal = max(retVal, items[middle][1])
                left = middle + 1

        return retVal

    def maximumBeauty(self, items: List[List[int]], queries: List[int]) -> List[int]:
        retVal = []

        items.sort(key=lambda x: x[0])

        maxBeauty = items[0][1]
        for item in items:
            maxBeauty = max(maxBeauty, item[1])
            item[1] = maxBeauty

        for query in queries:
            retVal.append(self.binarySearch(items, query))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for items, queries in zip(
            [[[1, 2], [3, 2], [2, 4], [5, 6], [3, 5]],
             [[1, 2], [1, 2], [1, 3], [1, 4]],
             [[10, 1000]]],
            [[1, 2, 3, 4, 5, 6],
             [1],
             [5]]
        ):
            # /* Example
            #  *  Input: items = [[1,2],[3,2],[2,4],[5,6],[3,5]], queries = [1,2,3,4,5,6]
            #  *  Output: [2,4,5,5,6,6]
            #  *
            #  *  Input: items = [[1,2],[1,2],[1,3],[1,4]], queries = [1]
            #  *  Output: [4]
            #  *
            #  *  Input: items = [[10,1000]], queries = [5]
            #  *  Output: [0]
            #  */
            logging.info("Input: items = %s, queries = %s", items, queries)

            retVal = pSolution.maximumBeauty(items, queries)
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
