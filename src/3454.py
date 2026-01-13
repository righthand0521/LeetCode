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


class SegmentTree:
    def __init__(self, xs: List[int]):
        self.xs = xs
        self.n = len(xs) - 1
        self.count = [0] * (4 * self.n)
        self.covered = [0] * (4 * self.n)

    def update(self, qleft, qright, qval, left, right, pos) -> None:
        if (self.xs[right + 1] <= qleft) or (self.xs[left] >= qright):
            return

        if (qleft <= self.xs[left]) and (self.xs[right + 1] <= qright):
            self.count[pos] += qval
        else:
            middle = (left + right) // 2
            self.update(qleft, qright, qval, left, middle, pos * 2 + 1)
            self.update(qleft, qright, qval, middle + 1, right, pos * 2 + 2)

        if self.count[pos] > 0:
            self.covered[pos] = self.xs[right + 1] - self.xs[left]
        else:
            if left == right:
                self.covered[pos] = 0
            else:
                self.covered[pos] = (self.covered[pos * 2 + 1] + self.covered[pos * 2 + 2])

    def query(self) -> int:
        retVal = self.covered[0]

        return retVal


class Solution:
    def separateSquares(self, squares: List[List[int]]) -> float:
        retVal = 0

        events = []
        xs = set()
        for x, y, l in squares:
            events.append((y, 1, x, x + l))
            events.append((y + l, -1, x, x + l))
            xs.update([x, x + l])
        xs = sorted(xs)
        psegmenttree = SegmentTree(xs)
        events.sort()

        psum = []
        widths = []
        totalarea = 0.0
        previousy = events[0][0]

        # scan: calculate total area and record intermediate states
        for y, delta, xl, xr in events:
            length = psegmenttree.query()
            totalarea += (length * (y - previousy))
            psegmenttree.update(xl, xr, delta, 0, psegmenttree.n - 1, 0)
            # record prefix sums and widths
            psum.append(totalarea)
            widths.append(psegmenttree.query())
            previousy = y

        # calculate the target area (half rounded up)
        target = (totalarea + 1) // 2

        # find the first position greater than or equal to target using binary search
        i = bisect_left(psum, target) - 1

        # get the corresponding area, width, and height
        area = psum[i]
        width = widths[i]
        height = events[i][0]

        retVal = height + (totalarea - area * 2) / (width * 2.0)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for squares in [[[0, 0, 1], [2, 2, 1]], [[0, 0, 2], [1, 1, 1]]]:
            # /* Example
            #  *  Input: squares = [[0,0,1],[2,2,1]]
            #  *  Output: 1.00000
            #  *
            #  *  Input: squares = [[0,0,2],[1,1,1]]
            #  *  Output: 1.00000
            #  */
            logging.info("Input: squares = %s", squares)

            retVal = pSolution.separateSquares(squares)
            logging.info("Output: %.5f", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
