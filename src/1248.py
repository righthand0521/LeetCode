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
    def numberOfSubarrays(self, nums: List[int], k: int) -> int:
        retVal = 0

        numsSize = len(nums)

        initialGap = 0
        qsize = 0
        start = 0
        for end in range(numsSize):
            # If current element is odd, increment qsize by 1.
            if nums[end] % 2 == 1:
                qsize += 1

            if qsize == k:
                initialGap = 0

                while qsize == k:   # Calculate the number of even elements in the beginning of subarray.
                    qsize -= nums[start] % 2
                    initialGap += 1
                    start += 1

            retVal += initialGap

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[1, 1, 2, 1, 1], [2, 4, 6], [2, 2, 2, 1, 2, 2, 1, 2, 2, 2]], [3, 1, 2]):
            # /* Example
            #  *  Input: nums = [1,1,2,1,1], k = 3
            #  *  Output: 2
            #  *
            #  *  Input: nums = [2,4,6], k = 1
            #  *  Output: 0
            #  *
            #  *  Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2
            #  *  Output: 16
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.numberOfSubarrays(nums, k)
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
