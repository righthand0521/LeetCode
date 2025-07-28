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
    def summaryRanges(self, nums: List[int]) -> List[str]:
        retVal = []

        numsSize = len(nums)

        idx = 0
        while idx < numsSize:
            tmp = nums[idx]
            while (idx+1 < numsSize) and (nums[idx]+1 == nums[idx+1]):
                idx += 1

            if tmp == nums[idx]:
                retVal.append(str(tmp))
            else:
                retVal.append(str(tmp)+"->"+str(nums[idx]))

            idx += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[0, 1, 2, 4, 5, 7], [0, 2, 3, 4, 6, 8, 9]]:
            # /* Example
            #  *  Input: nums = [0,1,2,4,5,7]
            #  *  Output: ["0->2","4->5","7"]
            #  *
            #  *  Input: nums = [0,2,3,4,6,8,9]
            #  *  Output: ["0","2->4","6","8->9"]
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.summaryRanges(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
