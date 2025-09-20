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


class Router:
    def __init__(self, memoryLimit: int):
        self.memLimit = memoryLimit
        self.length = 0
        self.isExist = set()
        self.sameDestQue = {}
        self.que = []

    def addPacket(self, source: int, destination: int, timestamp: int) -> bool:
        retVal = False

        packet = (source, destination, timestamp)
        if packet in self.isExist:
            return retVal

        if self.length == self.memLimit:
            self.forwardPacket()
        self.length += 1
        self.que.append(packet)

        if destination not in self.sameDestQue:
            self.sameDestQue[destination] = SortedList()
        self.sameDestQue[destination].add(timestamp)
        self.isExist.add(packet)

        retVal = True

        return retVal

    def forwardPacket(self) -> List[int]:
        retVal = []

        if self.que:
            packet = self.que.pop(0)
            retVal = list(packet)
            self.isExist.remove(packet)
            self.sameDestQue[retVal[1]].remove(retVal[2])
            self.length -= 1

        return retVal

    def getCount(self, destination: int, startTime: int, endTime: int) -> int:
        retVal = 0

        if destination not in self.sameDestQue:
            return retVal
        sl = self.sameDestQue[destination]
        retVal = sl.bisect_right(endTime) - sl.bisect_left(startTime)

        return retVal

# Your Router object will be instantiated and called as such:
# obj = Router(memoryLimit)
# param_1 = obj.addPacket(source,destination,timestamp)
# param_2 = obj.forwardPacket()
# param_3 = obj.getCount(destination,startTime,endTime)


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        for methods, val in zip(
            [
                ["Router", "addPacket", "addPacket", "addPacket", "addPacket",
                 "addPacket", "forwardPacket", "addPacket", "getCount"],
                ["Router", "addPacket", "forwardPacket", "forwardPacket"]
            ],
            [
                [[3], [1, 4, 90], [2, 5, 90], [1, 4, 90], [3, 5, 95], [4, 5, 105], [], [5, 2, 110], [5, 100, 110]],
                [[2], [7, 4, 90], [], []]
            ]
        ):
            # /* Example
            #  *  Input:
            #  *  ["Router","addPacket","addPacket","addPacket","addPacket","addPacket","forwardPacket","addPacket","getCount"]
            #  *  [[3],[1,4,90],[2,5,90],[1,4,90],[3,5,95],[4,5,105],[],[5,2,110],[5,100,110]]
            #  *  Output:
            #  *  [null,true,true,false,true,true,[2,5,90],true,1]
            #  *
            #  *  Input:
            #  *  ["Router","addPacket","forwardPacket","forwardPacket"]
            #  *  [[2],[7,4,90],[],[]]
            #  *  Output:
            #  *  [null,true,[7,4,90],[]]
            #  */
            logging.info("Input:")
            logging.info("%s", methods)
            logging.info("%s", val)

            displayStr = []
            for key, value in zip(methods, val):
                if key == "Router":
                    obj = Router(value)
                    displayStr.append(None)
                elif key == "addPacket":
                    retVal = obj.addPacket(value[0], value[1], value[2])
                    displayStr.append(retVal)
                elif key == "forwardPacket":
                    retVal = obj.forwardPacket()
                    displayStr.append(retVal)
                elif key == "getCount":
                    retVal = obj.getCount(value[0], value[1], value[2])
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

        print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

        sys.exit(0)
