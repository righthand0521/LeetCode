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
    def minKBitFlips(self, nums: List[int], k: int) -> int:
        retVal = 0

        numsSize = len(nums)
        revCnt = 0
        for i in range(numsSize):
            if (i >= k) and (nums[i - k] > 1):
                revCnt ^= 1
                nums[i - k] -= 2

            if nums[i] == revCnt:
                if i + k > numsSize:
                    retVal = -1
                    break
                retVal += 1
                revCnt ^= 1
                nums[i] += 2

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[0, 1, 0], [1, 1, 0], [0, 0, 0, 1, 0, 1, 1, 0]], [1, 2, 3]):
            # /* Example
            #  *  Input: nums = [0,1,0], k = 1
            #  *  Output: 2
            #  *
            #  *  Input: nums = [1,1,0], k = 2
            #  *  Output: -1
            #  *
            #  *  Input: nums = [0,0,0,1,0,1,1,0], k = 3
            #  *  Output: 3
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.minKBitFlips(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
