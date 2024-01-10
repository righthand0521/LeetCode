import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop
from sortedcontainers import SortedList


def logging_setting():
    LOG_LEVEL = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt='%Y/%m/%d %H:%M:%S')


class MedianFinder:
    def __init__(self):
        # 1: MaxHeap and MinHeap
        # 2: SortedList
        self.method = 1

        if self.method == 1:
            print("MaxHeap and MinHeap")
            self.minHeap = []
            self.maxHeap = []
        elif self.method == 2:
            print("SortedList")
            self.arr = SortedList()

    def addNum(self, num: int) -> None:
        if self.method == 1:
            heappush(self.maxHeap, -num)
            heappush(self.minHeap, -heappop(self.maxHeap))
            if len(self.minHeap) > len(self.maxHeap):
                heappush(self.maxHeap, -heappop(self.minHeap))
        elif self.method == 2:
            self.arr.add(num)

    def findMedian(self) -> float:
        if self.method == 1:
            if len(self.maxHeap) > len(self.minHeap):
                return -self.maxHeap[0]
            return (-self.maxHeap[0] + self.minHeap[0]) / 2
        elif self.method == 2:
            n = len(self.arr)
            if n % 2 == 1:
                return self.arr[n//2]
            return (self.arr[n//2] + self.arr[n//2-1]) / 2

# Your MedianFinder object will be instantiated and called as such:
# obj = MedianFinder()
# obj.addNum(num)
# param_2 = obj.findMedian()


if __name__ == "__main__":
    logging_setting()

    logging.info("sys.version: %s", sys.version)
    print("")
    try:
        print("Input")
        print(
            '["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]')
        print("[[], [1], [2], [], [3], []]")

        obj = MedianFinder()
        obj.addNum(1)
        obj.addNum(2)
        ret1 = obj.findMedian()
        obj.addNum(3)
        ret2 = obj.findMedian()

        print("Output")
        print('[null, null, null, {:f}, null, {:f}]'.format(ret1, ret2))

        print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass

    sys.exit(0)
