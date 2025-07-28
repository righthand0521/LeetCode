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
    def xorQueries(self, arr: List[int], queries: List[List[int]]) -> List[int]:
        retVal = []

        prefixSum = [0]
        for key, value in enumerate(arr):
            prefixSum.append(prefixSum[key] ^ arr[key])

        for query in queries:
            retVal.append(prefixSum[query[1]+1] ^ prefixSum[query[0]])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr, queries in zip([[1, 3, 4, 8], [4, 8, 2, 10]],
                                [[[0, 1], [1, 2], [0, 3], [3, 3]], [[2, 3], [1, 3], [0, 0], [0, 3]]]):
            # /* Example
            #  *  Input: arr = [1,3,4,8], queries = [[0,1],[1,2],[0,3],[3,3]]
            #  *  Output: [2,7,14,8]
            #  *
            #  *  Input: arr = [4,8,2,10], queries = [[2,3],[1,3],[0,0],[0,3]]
            #  *  Output: [8,0,4,4]
            #  */
            logging.info("Input: arr = %s, queries = %s", arr, queries)

            retVal = pSolution.xorQueries(arr, queries)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
