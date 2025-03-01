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
    def applyOperations(self, nums: List[int]) -> List[int]:
        retVal = nums

        numsSize = len(nums)
        writeIndex = 0  # Pointer to place non-zero elements
        for index in range(numsSize):
            # Step 1: Merge adjacent equal elements if they are non-zero
            if (index < numsSize - 1) and (nums[index] == nums[index + 1]) and (nums[index] != 0):
                nums[index] *= 2
                nums[index + 1] = 0

            # Step 2: Shift non-zero elements to the front
            if nums[index] != 0:
                if index != writeIndex:
                    nums[index], nums[writeIndex] = nums[writeIndex], nums[index]
                writeIndex += 1

        retVal = nums

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, 2, 2, 1, 1, 0], [0, 1]]:
            # /* Example
            #  *  Input: nums = [1,2,2,1,1,0]
            #  *  Output: [1,4,2,0,0,0]
            #  *
            #  *  Input: nums = [0,1]
            #  *  Output: [1,0]
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.applyOperations(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
