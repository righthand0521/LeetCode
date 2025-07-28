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
    def majorityElement(self, nums: List[int]) -> List[int]:
        retVal = []

        # /* Boyer–Moore majority vote algorithm
        #  *  https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_majority_vote_algorithm
        #  */
        candidate1 = 0
        count1 = 0
        candidate2 = 0
        count2 = 0
        for num in nums:
            if count1 > 0 and candidate1 == num:
                count1 += 1
            elif count2 > 0 and candidate2 == num:
                count2 += 1
            elif count1 == 0:
                candidate1 = num
                count1 += 1
            elif count2 == 0:
                candidate2 = num
                count2 += 1
            else:
                count1 -= 1
                count2 -= 1

        check1 = 0
        check2 = 0
        for num in nums:
            if num == candidate1 and count1 > 0:
                check1 += 1
            elif num == candidate2 and count2 > 0:
                check2 += 1

        numsSize = len(nums)
        if check1 > numsSize/3:
            retVal.append(candidate1)
        if check2 > numsSize/3:
            retVal.append(candidate2)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[3, 2, 3], [1], [1, 2]]:
            # /* Example
            #  *  Input: nums = [3,2,3]
            #  *  Output: [3]
            #  *
            #  *  Input: nums = [1]
            #  *  Output: [1]
            #  *
            #  *  Input: nums = [1,2]
            #  *  Output: [1,2]
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.majorityElement(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
