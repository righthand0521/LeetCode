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
    def __init__(self) -> None:
        self.method = 1

    def backtracking(self, sol: List[int], nums: List[int], check: int, answer: List[List[int]]) -> None:
        if len(sol) == len(nums):
            answer.append(sol)
            return

        for i in range(len(nums)):
            if check[i] == 1:
                continue
            check[i] = 1
            self.backtracking(sol+[nums[i]], nums, check, answer)
            check[i] = 0

    def permute(self, nums: List[int]) -> List[List[int]]:
        retVal = []

        if self.method == 1:
            check = [0 for i in range(len(nums))]
            self.backtracking([], nums, check, retVal)
        elif self.method == 2:
            from itertools import permutations
            retVal = list(permutations(nums))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, 2, 3], [0, 1], [1]]:
            # /* Example
            #  *  Input: nums = [1,2,3]
            #  *  Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
            #  *
            #  *  Input: nums = [0,1]
            #  *  Output: [[0,1],[1,0]]
            #  *
            #  *  Input: nums = [1]
            #  *  Output: [[1]]
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.permute(nums)
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
