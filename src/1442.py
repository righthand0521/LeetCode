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
    def countTriplets(self, arr: List[int]) -> int:
        retVal = 0

        arrSize = len(arr)

        # Dictionaries to store counts and totals of XOR values encountered
        count_map = defaultdict(int)
        count_map[0] = 1
        total_map = defaultdict(int)

        # Iterating through the array
        prefix = 0
        for i in range(arrSize):
            # Calculating XOR prefix
            prefix ^= arr[i]

            # Calculating contribution of current element to the result
            retVal += count_map[prefix] * i - total_map[prefix]

            # Updating total count of current XOR value
            total_map[prefix] += i + 1
            count_map[prefix] += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr in [[2, 3, 1, 6, 7], [1, 1, 1, 1, 1]]:
            # /* Example
            #  *  Input: arr = [2,3,1,6,7]
            #  *  Output: 4
            #  *
            #  *  Input: arr = [1,1,1,1,1]
            #  *  Output: 10
            #  */
            logging.info("Input: arr = %s", arr)

            retVal = pSolution.countTriplets(arr)
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
