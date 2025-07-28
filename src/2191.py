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
    def sortJumbled(self, mapping: List[int], nums: List[int]) -> List[int]:
        retVal = []

        storePairs = []
        for idx, num in enumerate(nums):
            if num == 0:    # 0 <= nums[i] < 10^9
                storePairs.append((mapping[num], idx))
                continue

            mappedValue = 0
            shift = 1
            while num > 0:
                mappedValue += (mapping[num % 10] * shift)
                num //= 10
                shift *= 10
            storePairs.append((mappedValue, idx))

        storePairs.sort()
        for _, idx in storePairs:
            retVal.append(nums[idx])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for mapping, nums in zip([[8, 9, 4, 0, 2, 1, 3, 5, 7, 6], [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]],
                                 [[991, 338, 38], [789, 456, 123]]):
            # /* Example
            #  *  Input: mapping = [8,9,4,0,2,1,3,5,7,6], nums = [991,338,38]
            #  *  Output: [338,38,991]
            #  *
            #  *  Input: mapping = [0,1,2,3,4,5,6,7,8,9], nums = [789,456,123]
            #  *  Output: [123,456,789]
            #  */
            logging.info("Input: mapping = %s, nums = %s", mapping, nums)

            retVal = pSolution.sortJumbled(mapping, nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
