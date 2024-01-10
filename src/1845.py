import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop


def logging_setting():
    LOG_LEVEL = logging.INFO  # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt="%Y/%m/%d %H:%M:%S",
    )


class SeatManager:
    def __init__(self, n: int):
        self.seats = [i for i in range(1, n + 1)]

    def reserve(self) -> int:
        retVal = heappop(self.seats)

        return retVal

    def unreserve(self, seatNumber: int) -> None:
        heappush(self.seats, seatNumber)


# Your SeatManager object will be instantiated and called as such:
# obj = SeatManager(n)
# param_1 = obj.reserve()
# obj.unreserve(seatNumber)


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, seat in zip(
            [
                [
                    "SeatManager",
                    "reserve",
                    "reserve",
                    "unreserve",
                    "reserve",
                    "reserve",
                    "reserve",
                    "reserve",
                    "unreserve",
                ]
            ],
            [[[5], [], [], [2], [], [], [], [], [5]]],
        ):
            # /* Example
            #  *  Input
            #  *  ["SeatManager", "reserve", "reserve", "unreserve", "reserve", "reserve", "reserve", "reserve", "unreserve"]
            #  *  [[5], [], [], [2], [], [], [], [], [5]]
            #  *  Output
            #  *  [null, 1, 2, null, 2, 3, 4, 5, null]
            #  */
            logging.info("%s", methods)
            logging.info("%s", seat)

            displayStr = []
            for key, value in zip(methods, seat):
                if key == "SeatManager":
                    obj = SeatManager(value[0])
                    displayStr.append(None)
                elif key == "reserve":
                    retVal = obj.reserve()
                    displayStr.append(retVal)
                elif key == "unreserve":
                    obj.unreserve(value[0])
                    displayStr.append(None)
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
