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
    def __init__(self):
        self.adjacent = None
        self.sum = 0
        self.ret = 0

    def calc(self, part1: int, part2: int, part3: int) -> int:
        retVal = max(part1, part2, part3) - min(part1, part2, part3)

        return retVal

    def dfs(self, nums: List[int], x: int, f: int) -> int:
        retVal = nums[x]

        for y in self.adjacent[x]:
            if y == f:
                continue
            retVal ^= self.dfs(nums, y, x)

        for y in self.adjacent[x]:
            if y == f:
                self.dfs2(nums, y, x, retVal, x)

        return retVal

    def dfs2(self, nums: List[int], x: int, f: int, oth: int, anc: int) -> int:
        retVal = nums[x]

        for y in self.adjacent[x]:
            if y == f:
                continue
            retVal ^= self.dfs2(nums, y, x, oth, anc)

        if f != anc:
            self.ret = min(self.ret, self.calc(oth, retVal, self.sum ^ oth ^ retVal))

        return retVal

    def minimumScore(self, nums: List[int], edges: List[List[int]]) -> int:
        retVal = 0

        numsSize = len(nums)

        self.adjacent = [[] for _ in range(numsSize)]
        for u, v in edges:
            self.adjacent[u].append(v)
            self.adjacent[v].append(u)

        self.sum = 0
        for x in nums:
            self.sum ^= x

        self.ret = float("inf")
        self.dfs(nums, 0, -1)
        retVal = self.ret

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, edges in [
            [[1, 5, 5, 4, 11], [[0, 1], [1, 2], [1, 3], [3, 4]]],
            [[5, 5, 2, 4, 4, 2], [[0, 1], [1, 2], [5, 2], [4, 3], [1, 3]]]
        ]:
            # /* Example
            #  *  Input: nums = [1,5,5,4,11], edges = [[0,1],[1,2],[1,3],[3,4]]
            #  *  Output: 9
            #  *
            #  *  Input: nums = [5,5,2,4,4,2], edges = [[0,1],[1,2],[5,2],[4,3],[1,3]]
            #  *  Output: 0
            #  */
            logging.info("Input: nums = %s, edges = %s", nums, edges)

            retVal = pSolution.minimumScore(nums, edges)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
