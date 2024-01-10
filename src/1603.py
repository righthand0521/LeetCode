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


class ParkingSystem:
    def __init__(self, big: int, medium: int, small: int):
        self.big = big
        self.medium = medium
        self.small = small

    def addCar(self, carType: int) -> bool:
        retVal = False

        if carType == 1:
            if self.big > 0:
                self.big -= 1
                retVal = True
        elif carType == 2:
            if self.medium > 0:
                self.medium -= 1
                retVal = True
        elif carType == 3:
            if self.small > 0:
                self.small -= 1
                retVal = True

        return retVal

# Your ParkingSystem object will be instantiated and called as such:
# obj = ParkingSystem(big, medium, small)
# param_1 = obj.addCar(carType)


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, carType in zip([["ParkingSystem", "addCar", "addCar", "addCar", "addCar"]],
                                    [[[1, 1, 0], [1], [2], [3], [1]]]):
            # /* Example
            #  *  Input
            #  *  ["ParkingSystem", "addCar", "addCar", "addCar", "addCar"]
            #  *  [[1, 1, 0], [1], [2], [3], [1]]
            #  *  Output
            #  *  [null, true, true, false, false]
            #  */
            logging.info("%s", methods)
            logging.info("%s", carType)

            displayStr = []
            for key, value in zip(methods, carType):
                if key == "ParkingSystem":
                    obj = ParkingSystem(value[0], value[1], value[2])
                    displayStr.append(None)
                elif key == "addCar":
                    retVal = obj.addCar(value[0])
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
