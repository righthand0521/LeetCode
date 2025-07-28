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
    def minOperations(self, nums: List[int], x: int) -> int:
        retVal = -1

        target = sum(nums) - x
        if target < 0:
            return retVal

        # /* https://leetcode.cn/problems/minimum-operations-to-reduce-x-to-zero/solutions/485281/shi-yong-hua-dong-chuang-kou-zhao-zhong-jian-zui-c/
        #  *  sum(fragment of nums) = sum(nums) - x
        #  *  Example
        #  *  +-------------------+   +----------------------------+
        #  *  | sum-x     | x=5   |   | x=10  | sum-x  | x=10      |
        #  *  | = 11-5    |       |   |       | =30-10 |           |
        #  *  +-------------------+   +----------------------------+
        #  *  | 1 | 1 | 4 | 2 | 3 |   | 3 | 2 |   20   | 1 | 1 | 3 |
        #  *  +-------------------+   +----------------------------+
        #  */
        numsSize = len(nums)
        sumOfNums = 0
        start = 0
        for tail in range(numsSize):
            sumOfNums += nums[tail]
            while sumOfNums > target:
                sumOfNums -= nums[start]
                start += 1

            if sumOfNums == target:
                retVal = max(retVal, tail-start+1)

        if retVal != -1:
            retVal = numsSize - retVal

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, x in zip([[1, 1, 4, 2, 3], [5, 6, 7, 8, 9], [3, 2, 20, 1, 1, 3], [1, 1]], [5, 4, 10, 3]):
            # /* Example
            #  *  Input: nums = [1,1,4,2,3], x = 5
            #  *  Output: 2
            #  *
            #  *  Input: nums = [5,6,7,8,9], x = 4
            #  *  Output: -1
            #  *
            #  *  Input: nums = [3,2,20,1,1,3], x = 10
            #  *  Output: 5
            #  *
            #  *  Input: nums = [1,1], x = 3
            #  *  Output: -1
            #  */
            logging.info("Input: nums = %s, x = %s", nums, x)

            retVal = pSolution.minOperations(nums, x)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
