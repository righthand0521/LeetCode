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
    def fourSum(self, nums: List[int], target: int) -> List[List[int]]:
        retVal = []

        numsSize = len(nums)
        if numsSize < 4:
            return retVal

        nums.sort()
        numsSize = len(nums)
        for a in range(numsSize-3):
            # Notice that the order of the output and the order of the triplets does not matter.
            if (a > 0) and (nums[a-1] == nums[a]):
                continue

            for b in range(a + 1, numsSize - 2):
                # Notice that the order of the output and the order of the triplets does not matter.
                if (b > a + 1) and (nums[b-1] == nums[b]):
                    continue

                c = b + 1
                d = numsSize - 1
                while c < d:
                    if nums[a] + nums[b] + nums[c] + nums[d] < target:
                        c += 1
                    elif nums[a] + nums[b] + nums[c] + nums[d] > target:
                        d -= 1
                    else:
                        # Notice that the order of the output and the order of the triplets does not matter.
                        if (c > b + 1) and (nums[c - 1] == nums[c]):
                            c += 1
                            continue

                        retVal.append([nums[a], nums[b], nums[c], nums[d]])
                        c += 1
                        d -= 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, target in zip(
                [[1, 0, -1, 0, -2, 2], [2, 2, 2, 2, 2], [1000000000, 1000000000, 1000000000, 1000000000]], [0, 8, 0]):
            # /* Example
            #  *  Input: nums = [1,0,-1,0,-2,2], target = 0
            #  *  Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
            #  *
            #  *  Input: nums = [2,2,2,2,2], target = 8
            #  *  Output: [[2,2,2,2]]
            #  *
            #  *  Input: nums = [1000000000,1000000000,1000000000,1000000000], target = 0
            #  *  Output: []
            #  */
            logging.info("Input: nums = %s, target = %s", nums, target)

            retVal = pSolution.fourSum(nums, target)
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
