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
    def __init__(self):
        self.method = 1

    def minimizeArrayValue(self, nums: List[int]) -> int:
        retVal = 0

        if self.method == 1:
            print("Binary Search")

            left = 0
            right = max(nums)
            while left < right:
                middle = left + (right - left) // 2

                operationFlag = True
                operation = 0
                for num in nums:
                    if num <= middle:
                        operation += (middle - num)
                        continue

                    if operation < (num - middle):
                        operationFlag = False
                        break
                    operation -= (num - middle)

                if operationFlag == False:
                    left = middle + 1
                else:
                    right = middle
            retVal = left
        elif self.method == 2:
            print("Average")

            # https://leetcode.com/problems/minimize-maximum-of-array/solutions/2706521/java-c-python-prefix-sum-average-o-n/
            prefixSum = list(accumulate(nums))
            prefixSumSize = len(prefixSum)
            for i in range(prefixSumSize):
                retVal = max(retVal, ((prefixSum[i] + i) // (i + 1)))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[3, 7, 1, 6], [10, 1]]:
            # /* Example
            #  *  Input: nums = [3,7,1,6]
            #  *  Output: 5
            #  *
            #  *  Input: nums = [10,1]
            #  *  Output: 10
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.minimizeArrayValue(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
