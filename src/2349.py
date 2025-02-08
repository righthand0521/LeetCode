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


class NumberContainers:
    def __init__(self):
        self.numberToIndices = defaultdict(list)  # Map to store number -> min heap of indices
        self.indexToNumbers = {}  # Map to store index -> number

    def change(self, index: int, number: int) -> None:
        self.indexToNumbers[index] = number  # Update index to number mapping
        heappush(self.numberToIndices[number], index)  # Add index to the min heap for this number

    def find(self, number: int) -> int:
        retVal = -1

        # If number doesn't exist in our map
        if not self.numberToIndices[number]:
            return retVal

        # Keep checking top element until we find valid index
        while self.numberToIndices[number]:
            index = self.numberToIndices[number][0]

            # If index still maps to our target number, return it
            if self.indexToNumbers.get(index) == number:
                retVal = index
                break

            # Otherwise remove this stale index
            heappop(self.numberToIndices[number])

        return retVal

# Your NumberContainers object will be instantiated and called as such:
# obj = NumberContainers()
# obj.change(index,number)
# param_2 = obj.find(number)


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, val in zip(
            [["NumberContainers", "find", "change", "change", "change", "change", "find", "change", "find"]],
            [[[], [10], [2, 10], [1, 10], [3, 10], [5, 10], [10], [1, 20], [10]]]
        ):
            # /* Example
            #  *  Input
            #  *  ["NumberContainers", "find", "change", "change", "change", "change", "find", "change", "find"]
            #  *  [[], [10], [2, 10], [1, 10], [3, 10], [5, 10], [10], [1, 20], [10]]
            #  *  Output
            #  *  [null, -1, null, null, null, null, 1, null, 2]
            #  */
            logging.info("%s", methods)
            logging.info("%s", val)

            displayStr = []
            for key, value in zip(methods, val):
                if key == "NumberContainers":
                    obj = NumberContainers()
                    displayStr.append(None)
                elif key == "change":
                    obj.change(value[0], value[1])
                    displayStr.append(None)
                elif key == "find":
                    retVal = obj.find(value[0])
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
