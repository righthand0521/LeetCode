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
    def isPossibleDivide(self, nums: List[int], k: int) -> bool:
        retVal = False

        handSize = len(nums)
        if handSize % k > 0:
            return retVal

        nums.sort()

        count = Counter(nums)
        for x in nums:
            if count[x] == 0:
                continue

            for num in range(x, x + k):
                if count[num] == 0:
                    return retVal
                count[num] -= 1
        retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[1, 2, 3, 3, 4, 4, 5, 6], [3, 2, 1, 2, 3, 4, 3, 4, 5, 9, 10, 11], [1, 2, 3, 4]], [4, 3, 3]):
            # /* Example
            #  *  Input: nums = [1,2,3,3,4,4,5,6], k = 4
            #  *  Output: true
            #  *
            #  *  Input: nums = [3,2,1,2,3,4,3,4,5,9,10,11], k = 3
            #  *  Output: true
            #  *
            #  *  Input: nums = [1,2,3,4], k = 3
            #  *  Output: false
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.isPossibleDivide(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
