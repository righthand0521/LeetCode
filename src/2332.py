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


class Solution:
    def latestTimeCatchTheBus(self, buses: List[int], passengers: List[int], capacity: int) -> int:
        retVal = 0

        #
        busesSize = len(buses)
        busesIdx = 0
        buses.sort()
        passengersSize = len(passengers)
        passengersIdx = 0
        passengers.sort()

        #
        capacityIdx = 0
        while (busesIdx < (busesSize - 1)) and (passengersIdx < passengersSize):
            if (passengers[passengersIdx] <= buses[busesIdx]) and (capacityIdx < capacity):
                passengersIdx += 1
                capacityIdx += 1
            else:
                busesIdx += 1
                capacityIdx = 0
        capacityIdx = 0
        while (passengersIdx < passengersSize) and \
                (passengers[passengersIdx] <= buses[busesSize - 1]) and \
                (capacityIdx < capacity):
            passengersIdx += 1
            capacityIdx += 1

        #
        if capacityIdx < capacity:
            retVal = buses[busesSize - 1]
        else:
            retVal = passengers[passengersIdx - 1]
        passengersIdx -= 1
        while (passengersIdx >= 0) and (retVal == passengers[passengersIdx]):
            retVal = passengers[passengersIdx] - 1
            passengersIdx -= 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for buses, passengers, capacity in zip([[10, 20], [20, 30, 10]],
                                               [[2, 17, 18, 19], [
                                                   19, 13, 26, 4, 25, 11, 21]],
                                               [2, 2]):
            # /* Example
            #  *  Input: buses = [10,20], passengers = [2,17,18,19], capacity = 2
            #  *  Output: 16
            #  *
            #  *  Input: buses = [20,30,10], passengers = [19,13,26,4,25,11,21], capacity = 2
            #  *  Output: 20
            #  */
            logging.info(
                "Input: buses = %s, passengers = %s, capacity = %s", buses, passengers, capacity)

            retVal = pSolution.latestTimeCatchTheBus(
                buses, passengers, capacity)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
