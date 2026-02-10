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


class LazyTag:
    def __init__(self) -> None:
        self.to_add = 0

    def add(self, other) -> "LazyTag":
        retVal = None

        self.to_add += other.to_add
        retVal = self

        return retVal

    def has_tag(self) -> bool:
        retVal = (self.to_add != 0)

        return retVal

    def clear(self) -> None:
        self.to_add = 0


class SegmentTreeNode:
    def __init__(self) -> None:
        self.min_value = 0
        self.max_value = 0
        self.lazy_tag = LazyTag()


class SegmentTree:
    def __init__(self, data) -> None:
        self.n = len(data)
        self.tree = [SegmentTreeNode() for _ in range(self.n * 4 + 1)]
        self._build(data, 1, self.n, 1)

    def add(self, l, r, val) -> None:
        tag = LazyTag()
        tag.to_add = val
        self._update(l, r, tag, 1, self.n, 1)

    def find_last(self, start, val) -> int:
        retVal = -1

        if start <= self.n:
            retVal = self._find(start, self.n, val, 1, self.n, 1)

        return retVal

    def _apply_tag(self, i, tag) -> None:
        self.tree[i].min_value += tag.to_add
        self.tree[i].max_value += tag.to_add
        self.tree[i].lazy_tag.add(tag)

    def _pushdown(self, i) -> None:
        if self.tree[i].lazy_tag.has_tag() == False:
            return

        tag = LazyTag()
        tag.to_add = self.tree[i].lazy_tag.to_add
        self._apply_tag(i << 1, tag)
        self._apply_tag((i << 1) | 1, tag)
        self.tree[i].lazy_tag.clear()

    def _pushup(self, i) -> None:
        self.tree[i].min_value = min(self.tree[i << 1].min_value, self.tree[(i << 1) | 1].min_value)
        self.tree[i].max_value = max(self.tree[i << 1].max_value, self.tree[(i << 1) | 1].max_value)

    def _build(self, data, l, r, i) -> None:
        if l == r:
            self.tree[i].min_value = data[l - 1]
            self.tree[i].max_value = data[l - 1]
            return

        mid = l + ((r - l) >> 1)
        self._build(data, l, mid, i << 1)
        self._build(data, mid + 1, r, (i << 1) | 1)
        self._pushup(i)

    def _update(self, target_l, target_r, tag, l, r, i) -> None:
        if (target_l <= l) and (r <= target_r):
            self._apply_tag(i, tag)
            return

        self._pushdown(i)
        mid = l + ((r - l) >> 1)
        if target_l <= mid:
            self._update(target_l, target_r, tag, l, mid, i << 1)
        if target_r > mid:
            self._update(target_l, target_r, tag, mid + 1, r, (i << 1) | 1)
        self._pushup(i)

    def _find(self, target_l, target_r, val, l, r, i) -> int:
        retVal = -1

        if (self.tree[i].min_value > val) or (self.tree[i].max_value < val):
            return retVal

        if l == r:
            retVal = l
            return retVal

        self._pushdown(i)
        mid = l + ((r - l) >> 1)
        if target_r >= mid + 1:
            retVal = self._find(target_l, target_r, val, mid + 1, r, (i << 1) | 1)
            if retVal != -1:
                return retVal

        if (l <= target_r) and (mid >= target_l):
            retVal = self._find(target_l, target_r, val, l, mid, i << 1)
            return retVal

        return retVal


class Solution:
    def sgn(self, x: int) -> int:
        retVal = -1

        if x % 2 == 0:
            retVal = 1

        return retVal

    def longestBalanced(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        occurrences = defaultdict(deque)
        occurrences[nums[0]].append(1)

        prefix_sum = [0] * numsSize
        prefix_sum[0] = self.sgn(nums[0])
        for i in range(1, numsSize):
            prefix_sum[i] = prefix_sum[i - 1]
            occ = occurrences[nums[i]]
            if not occ:
                prefix_sum[i] += self.sgn(nums[i])
            occ.append(i + 1)

        seg = SegmentTree(prefix_sum)
        for i in range(numsSize):
            retVal = max(retVal, seg.find_last(i + retVal, 0) - i)
            next_pos = numsSize + 1
            occurrences[nums[i]].popleft()
            if occurrences[nums[i]]:
                next_pos = occurrences[nums[i]][0]
            seg.add(i + 1, next_pos - 1, -self.sgn(nums[i]))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[2, 5, 4, 3], [3, 2, 2, 5, 4], [1, 2, 3, 2]]:
            # /* Example
            #  *  Input: nums = [2,5,4,3]
            #  *  Output: 4
            #  *
            #  *  Input: nums = [3,2,2,5,4]
            #  *  Output: 5
            #  *
            #  *  Input: nums = [1,2,3,2]
            #  *  Output: 3
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.longestBalanced(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
