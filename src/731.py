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


class MyCalendarTwo:
    def __init__(self):
        self.bookings = []
        self.overlapBookings = []

    # Return True if the booking [start1, end1) & [start2, end2) overlaps.
    def doesOverlap(self, start1: int, end1: int, start2: int, end2: int) -> bool:
        retVal = False

        if max(start1, start2) < min(end1, end2):
            retVal = True

        return retVal

    # Return the overlapping booking between [start1, end1) & [start2, end2).
    def getOverlapped(self, start1: int, end1: int, start2: int, end2: int) -> tuple:
        retVal = max(start1, start2), min(end1, end2)

        return retVal

    def book(self, start: int, end: int) -> bool:
        retVal = False

        # Check if the new booking overlaps with any double-booked booking.
        for booking in self.overlapBookings:
            if self.doesOverlap(booking[0], booking[1], start, end) == True:
                return retVal

        # Add any new double overlaps that the current booking creates.
        for booking in self.bookings:
            if self.doesOverlap(booking[0], booking[1], start, end) == True:
                self.overlapBookings.append(self.getOverlapped(
                    booking[0], booking[1], start, end))

        # Add the new booking to the list of bookings.
        self.bookings.append((start, end))
        retVal = True

        return retVal

# Your MyCalendarTwo object will be instantiated and called as such:
# obj = MyCalendarTwo()
# param_1 = obj.book(start,end)


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, values in zip([["MyCalendarTwo", "book", "book", "book", "book", "book", "book"]],
                                   [[[], [10, 20], [50, 60], [10, 40], [5, 15], [5, 10], [25, 55]]]):
            # /* Example
            #  *  Input
            #  *  ["MyCalendarTwo", "book", "book", "book", "book", "book", "book"]
            #  *  [[], [10, 20], [50, 60], [10, 40], [5, 15], [5, 10], [25, 55]]
            #  *  Output
            #  *  [null, true, true, true, false, true, true]
            #  */
            logging.info("%s", methods)
            logging.info("%s", values)

            displayStr = []
            for key, value in zip(methods, values):
                if key == "MyCalendarTwo":
                    obj = MyCalendarTwo()
                    displayStr.append(None)
                elif key == "book":
                    retVal = obj.book(value[0], value[1])
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
