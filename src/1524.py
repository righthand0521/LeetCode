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
    def __init__(self) -> None:
        self.MODULO = 10 ** 9 + 7   # Since the answer can be very large, return it modulo 10^9 + 7.

    def numOfSubarrays(self, arr: List[int]) -> int:
        retVal = 0

        prefixSum = 0
        oddCount = 0
        evenCount = 1  # evenCount starts as 1 since the initial sum (0) is even
        for num in arr:
            prefixSum += num
            if prefixSum % 2 == 0:  # If current prefix sum is even, add the number of odd subarrays
                retVal += oddCount
                evenCount += 1
            else:  # If current prefix sum is odd, add the number of even subarrays
                retVal += evenCount
                oddCount += 1

            retVal %= self.MODULO  # To handle large results

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr in [[1, 3, 5],  [2, 4, 6], [1, 2, 3, 4, 5, 6, 7]]:
            # /* Example
            #  *  Input: arr = [1,3,5]
            #  *  Output: 4
            #  *
            #  *  Input: arr = [2,4,6]
            #  *  Output: 0
            #  *
            #  *  Input: arr = [1,2,3,4,5,6,7]
            #  *  Output: 16
            #  */
            logging.info("Input: arr = %s", arr)

            retVal = pSolution.numOfSubarrays(arr)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
