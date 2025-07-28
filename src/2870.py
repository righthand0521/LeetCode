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
    def minOperations(self, nums: List[int]) -> int:
        retVal = 0

        count = Counter(nums)
        for times in count.values():
            if times == 1:
                retVal = -1
                break

            operations = times // 3
            if times % 3 == 0:
                retVal += operations
            else:
                retVal += (operations + 1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[2, 3, 3, 2, 2, 4, 2, 3, 4], [2, 1, 2, 2, 3, 3]]:
            # /* Example
            #  *  Input: nums = [2,3,3,2,2,4,2,3,4]
            #  *  Output: 4
            #  *
            #  *  Input: nums = [2,1,2,2,3,3]
            #  *  Output: -1
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.minOperations(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
