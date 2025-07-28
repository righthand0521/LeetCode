import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from typing import List, Optional

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


class MyCalendar:
    def __init__(self):
        self.calendar = SortedList()

    def book(self, start: int, end: int) -> bool:
        retVal = False

        calendarSize = len(self.calendar)

        idx = self.calendar.bisect_right((start, end))
        if (idx > 0) and (self.calendar[idx-1][1] > start):
            return retVal
        elif (idx < calendarSize) and (self.calendar[idx][0] < end):
            return retVal

        self.calendar.add((start, end))
        retVal = True

        return retVal

# Your MyCalendar object will be instantiated and called as such:
# obj = MyCalendar()
# param_1 = obj.book(start,end)


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, values in zip([["MyCalendar", "book", "book", "book"]], [[[], [10, 20], [15, 25], [20, 30]]]):
            # /* Example
            #  *  Input
            #  *  ["MyCalendar", "book", "book", "book"]
            #  *  [[], [10, 20], [15, 25], [20, 30]]
            #  *  Output
            #  *  [null, true, false, true]
            #  */
            logging.info("%s", methods)
            logging.info("%s", values)

            displayStr = []
            for key, value in zip(methods, values):
                if key == "MyCalendar":
                    obj = MyCalendar()
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
