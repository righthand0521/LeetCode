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
    def numOfSubarrays(self, arr: List[int], k: int, threshold: int) -> int:
        retVal = 0

        arrSize = len(arr)

        prefixSum = 0
        for i in range(k-1):
            prefixSum += arr[i]

        for i in range(k-1, arrSize):
            prefixSum += arr[i]
            if prefixSum // k >= threshold:
                retVal += 1
            prefixSum -= arr[i-k+1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr, k, threshold in zip([[2, 2, 2, 2, 5, 5, 5, 8], [11, 13, 17, 23, 29, 31, 7, 5, 2, 3]], [3, 3], [4, 5]):
            # /* Example
            #  *  Input: arr = [2,2,2,2,5,5,5,8], k = 3, threshold = 4
            #  *  Output: 3
            #  *
            #  *  Input: arr = [11,13,17,23,29,31,7,5,2,3], k = 3, threshold = 5
            #  *  Output: 6
            #  */
            logging.info(
                "Input: nums = %s, k = %s, threshold = %s", arr, k, threshold)

            retVal = pSolution.numOfSubarrays(arr, k, threshold)
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
