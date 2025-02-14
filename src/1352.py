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


class ProductOfNumbers:
    def __init__(self):
        # Stores cumulative product of the stream
        # Initialize the product list with 1 to handle multiplication logic
        self.prefixProduct = [1]
        self.size = 0

    def add(self, num: int) -> None:
        if num == 0:
            # If num is 0, reset the cumulative products since multiplication with 0 invalidates previous products
            self.prefixProduct = [1]
            self.size = 0
        else:
            # Append the cumulative product of the current number with the last product
            self.prefixProduct.append(self.prefixProduct[self.size] * num)
            self.size += 1

    def getProduct(self, k: int) -> int:
        retVal = 0

        # Check if the requested product length exceeds the size of the valid product list
        if k > self.size:
            return retVal
        # Compute the product of the last k elements using division
        retVal = self.prefixProduct[self.size] // self.prefixProduct[self.size - k]

        return retVal


# Your ProductOfNumbers object will be instantiated and called as such:
# obj = ProductOfNumbers()
# obj.add(num)
# param_2 = obj.getProduct(k)


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, val in zip(
            [["ProductOfNumbers", "add", "add", "add", "add", "add",
                "getProduct", "getProduct", "getProduct", "add", "getProduct"]],
            [[[], [3], [0], [2], [5], [4], [2], [3], [4], [8], [2]]]
        ):
            # /* Example
            #  *  Input
            #  *  ["ProductOfNumbers","add","add","add","add","add","getProduct","getProduct","getProduct","add","getProduct"]
            #  *  [[],[3],[0],[2],[5],[4],[2],[3],[4],[8],[2]]
            #  *  Output
            #  *  [null,null,null,null,null,null,20,40,0,null,32]
            #  */
            logging.info("%s", methods)
            logging.info("%s", val)

            displayStr = []
            for key, value in zip(methods, val):
                if key == "ProductOfNumbers":
                    obj = ProductOfNumbers()
                    displayStr.append(None)
                elif key == "add":
                    obj.add(value[0])
                    displayStr.append(None)
                elif key == "getProduct":
                    retVal = obj.getProduct(value[0])
                    displayStr.append(retVal)
            logging.info("Output")
            logging.info("%s", displayStr)

            print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
