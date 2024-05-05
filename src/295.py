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


class MedianFinder:
    def __init__(self):
        self.minHeap = []
        self.maxHeap = []

    def addNum(self, num: int) -> None:
        heappush(self.maxHeap, -num)
        heappush(self.minHeap, -heappop(self.maxHeap))

        maxHeapSize = len(self.maxHeap)
        minHeapSize = len(self.minHeap)
        if minHeapSize > maxHeapSize:
            heappush(self.maxHeap, -heappop(self.minHeap))

    def findMedian(self) -> float:
        retVal = -self.maxHeap[0]

        maxHeapSize = len(self.maxHeap)
        minHeapSize = len(self.minHeap)
        if maxHeapSize > minHeapSize:
            return retVal
        retVal = (-self.maxHeap[0] + self.minHeap[0]) / 2

        return retVal


# Your MedianFinder object will be instantiated and called as such:
# obj = MedianFinder()
# obj.addNum(num)
# param_2 = obj.findMedian()

if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, num in zip([["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]],
                                [[None, 1, 2, None, 3, None]]):
            # /* Example
            #  *  Input
            #  *  ["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
            #  *  [[], [1], [2], [], [3], []]
            #  *  Output
            #  *  [null, null, null, 1.5, null, 2.0]
            #  */
            logging.info("%s", methods)
            displayStr = []
            for p in num:
                if p == None:
                    displayStr.append([])
                else:
                    displayStr.append(p)
            logging.info("%s", displayStr)

            displayStr = []
            obj = MedianFinder()
            for p, q in zip(methods, num):
                if p == "MedianFinder":
                    displayStr.append(None)
                elif p == "addNum":
                    obj.addNum(q)
                    displayStr.append(None)
                elif p == "findMedian":
                    retVal = obj.findMedian()
                    displayStr.append(retVal)
            logging.info("Output")
            logging.info("%s", displayStr)

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
