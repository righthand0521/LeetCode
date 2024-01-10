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


class StockSpanner:
    def __init__(self):
        self.stack = [(-1, float("inf"))]
        self.idx = -1

    def next(self, price: int) -> int:
        retVal = 0

        self.idx += 1
        while price >= self.stack[-1][1]:
            self.stack.pop()
        self.stack.append((self.idx, price))
        retVal = self.idx - self.stack[-2][0]

        return retVal

# Your StockSpanner object will be instantiated and called as such:
# obj = StockSpanner()
# param_1 = obj.next(price)


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, val in zip([["StockSpanner", "next", "next", "next", "next", "next", "next", "next"]],
                                [[[], [100], [80], [60], [70], [60], [75], [85]]]):
            # /* Example
            #  *  Input
            #  *  ["StockSpanner", "next", "next", "next", "next", "next", "next", "next"]
            #  *  [[], [100], [80], [60], [70], [60], [75], [85]]
            #  *  Output
            #  *  [null, 1, 1, 1, 2, 1, 4, 6]
            #  */
            logging.info("%s", methods)
            logging.info("%s", val)

            displayStr = []
            for key, value in zip(methods, val):
                if key == "StockSpanner":
                    obj = StockSpanner()
                    displayStr.append(None)
                elif key == "next":
                    retVal = obj.next(value[0])
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
