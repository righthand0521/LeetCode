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


class SnapshotArray:
    def __init__(self, length: int):
        self.id = 0
        self.history_records = [[[0, 0]] for _ in range(length)]

    def set(self, index: int, val: int) -> None:
        self.history_records[index].append([self.id, val])

    def snap(self) -> int:
        retVal = self.id

        self.id += 1

        return retVal

    def get(self, index: int, snap_id: int) -> int:
        retVal = 0

        snap_index = bisect_right(
            self.history_records[index], [snap_id, 10 ** 9])
        retVal = self.history_records[index][snap_index - 1][1]

        return retVal

# Your SnapshotArray object will be instantiated and called as such:
# obj = SnapshotArray(length)
# obj.set(index,val)
# param_2 = obj.snap()
# param_3 = obj.get(index,snap_id)


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, values in zip(
            [["SnapshotArray", "set", "snap", "set", "get"]],
                [[[3], [0, 5], [], [0, 6], [0, 0]]]):
            # /* Example
            #  *  Input: ["SnapshotArray","set","snap","set","get"]
            #  *  [[3],[0,5],[],[0,6],[0,0]]
            #  *  Output: [null,null,0,null,5]
            #  */
            logging.info("%s", methods)
            logging.info("%s", values)

            displayStr = []
            for key, value in zip(methods, values):
                if key == "SnapshotArray":
                    obj = SnapshotArray(value[0])
                    displayStr.append(None)
                elif key == "set":
                    obj.set(value[0], value[1])
                    displayStr.append(None)
                elif key == "snap":
                    retVal = obj.snap()
                    displayStr.append(retVal)
                elif key == "get":
                    retVal = obj.get(value[0], value[1])
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
