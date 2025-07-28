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


class UndergroundSystem:
    def __init__(self):
        self.startInfo = dict()
        self.table = dict()

    def checkIn(self, id: int, stationName: str, t: int) -> None:
        self.startInfo[id] = (stationName, t)

    def checkOut(self, id: int, stationName: str, t: int) -> None:
        startTime = self.startInfo[id][1]
        index = (self.startInfo[id][0], stationName)
        rec = self.table.get(index, (0, 0))
        self.table[index] = (rec[0] + t - startTime, rec[1] + 1)

    def getAverageTime(self, startStation: str, endStation: str) -> float:
        retVal = 0

        index = (startStation, endStation)
        sum, amount = self.table[index]
        retVal = sum / amount

        return retVal

# Your UndergroundSystem object will be instantiated and called as such:
# obj = UndergroundSystem()
# obj.checkIn(id,stationName,t)
# obj.checkOut(id,stationName,t)
# param_3 = obj.getAverageTime(startStation,endStation)


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, val in zip(
            [["UndergroundSystem", "checkIn", "checkIn", "checkIn", "checkOut", "checkOut", "checkOut",
              "getAverageTime", "getAverageTime", "checkIn", "getAverageTime", "checkOut", "getAverageTime"],
             ["UndergroundSystem", "checkIn", "checkOut", "getAverageTime", "checkIn", "checkOut", "getAverageTime",
              "checkIn", "checkOut", "getAverageTime"]],
            [[[], [45, "Leyton", 3], [32, "Paradise", 8], [27, "Leyton", 10], [45, "Waterloo", 15],
              [27, "Waterloo", 20], [32, "Cambridge", 22], [
                  "Paradise", "Cambridge"], ["Leyton", "Waterloo"],
              [10, "Leyton", 24], ["Leyton", "Waterloo"], [10, "Waterloo", 38], ["Leyton", "Waterloo"]],
             [[], [10, "Leyton", 3], [10, "Paradise", 8], ["Leyton", "Paradise"], [5, "Leyton", 10],
              [5, "Paradise", 16], ["Leyton", "Paradise"], [
                  2, "Leyton", 21], [2, "Paradise", 30],
              ["Leyton", "Paradise"]]]):
            # /* Example
            #  *  Input
            #  *  ["UndergroundSystem","checkIn","checkIn","checkIn","checkOut",
            #  *  "checkOut","checkOut","getAverageTime","getAverageTime","checkIn",
            #  *  "getAverageTime","checkOut","getAverageTime"]
            #  *  [[],[45,"Leyton",3],[32,"Paradise",8],[27,"Leyton",10],[45,"Waterloo",15],
            #  *  [27,"Waterloo",20],[32,"Cambridge",22],["Paradise","Cambridge"],["Leyton","Waterloo"],[10,"Leyton",24],
            #  *  ["Leyton","Waterloo"],[10,"Waterloo",38],["Leyton","Waterloo"]]
            #  *  Output
            #  *  [null,null,null,null,null,null,null,14.00000,11.00000,null,11.00000,null,12.00000]
            #  *
            #  *  Input
            #  *  ["UndergroundSystem","checkIn","checkOut","getAverageTime","checkIn",
            #  *  "checkOut","getAverageTime","checkIn","checkOut","getAverageTime"]
            #  *  [[],[10,"Leyton",3],[10,"Paradise",8],["Leyton","Paradise"],[5,"Leyton",10],
            #  *  [5,"Paradise",16],["Leyton","Paradise"],[2,"Leyton",21],[2,"Paradise",30],["Leyton","Paradise"]]
            #  *  Output
            #  *  [null,null,null,5.00000,null,null,5.50000,null,null,6.66667]
            #  */
            logging.info("%s", methods)
            logging.info("%s", val)

            displayStr = []
            for key, value in zip(methods, val):
                if key == "UndergroundSystem":
                    obj = UndergroundSystem()
                    displayStr.append(None)
                elif key == "checkIn":
                    obj.checkIn(value[0], value[1], value[2])
                    displayStr.append(None)
                elif key == "checkOut":
                    obj.checkOut(value[0], value[1], value[2])
                    displayStr.append(None)
                elif key == "getAverageTime":
                    retVal = obj.getAverageTime(value[0], value[1])
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
