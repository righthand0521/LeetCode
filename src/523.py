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
    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        retVal = False

        numsSize = len(nums)
        prefix_mod = 0
        mod_seen = {0: -1}
        for i in range(numsSize):
            prefix_mod = (prefix_mod + nums[i]) % k
            if prefix_mod in mod_seen:  # ensures that the size of subarray is at least 2
                if i - mod_seen[prefix_mod] > 1:
                    retVal = True
                    break
            else:   # mark the value of prefix_mod with the current index.
                mod_seen[prefix_mod] = i

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[23, 2, 4, 6, 7], [23, 2, 6, 4, 7], [23, 2, 6, 4, 7]], [6, 6, 13]):
            # /* Example:
            #  *  Input: nums = [23, 2, 4, 6, 7], k = 6
            #  *  Output: true
            #  *
            #  *  Input: nums = [23, 2, 6, 4, 7], k = 6
            #  *  Output: true
            #  *
            #  *  Input: nums = [23, 2, 6, 4, 7], k = 13
            #  *  Output: false
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.checkSubarraySum(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
