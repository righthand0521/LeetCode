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
    def findLeastNumOfUniqueInts(self, arr: List[int], k: int) -> int:
        retVal = 0

        arrCount = Counter(arr).most_common()
        arrCount.reverse()
        for _, times in arrCount:
            k -= times
            if k < 0:
                retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr, k in zip([[5, 5, 4], [4, 3, 1, 1, 3, 3, 2]], [1, 3]):
            # /* Example
            #  *  Input: arr = [5,5,4], k = 1
            #  *  Output: 1
            #  *
            #  *  Input: arr = [4,3,1,1,3,3,2], k = 3
            #  *  Output: 2
            #  */
            logging.info("Input: arr = %s, k = %s", arr, k)

            retVal = pSolution.findLeastNumOfUniqueInts(arr, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
