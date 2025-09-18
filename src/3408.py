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


class TaskManager:
    def __init__(self, tasks: List[List[int]]) -> None:
        self.taskInfo = {}
        self.heap = []
        for userId, taskId, priority in tasks:
            self.taskInfo[taskId] = [priority, userId]
            heappush(self.heap, [-priority, -taskId])

    def add(self, userId: int, taskId: int, priority: int) -> None:
        self.taskInfo[taskId] = [priority, userId]
        heappush(self.heap, [-priority, -taskId])

    def edit(self, taskId: int, newPriority: int) -> None:
        self.taskInfo[taskId][0] = newPriority
        heappush(self.heap, [-newPriority, -taskId])

    def rmv(self, taskId: int) -> None:
        self.taskInfo.pop(taskId)

    def execTop(self) -> int:
        retVal = -1

        while self.heap:
            priority, taskId = heappop(self.heap)
            priority, taskId = -priority, -taskId
            if priority == self.taskInfo.get(taskId, [-1, -1])[0]:
                retVal = self.taskInfo.pop(taskId)[1]
                break

        return retVal

# Your TaskManager object will be instantiated and called as such:
# obj = TaskManager(tasks)
# obj.add(userId,taskId,priority)
# obj.edit(taskId,newPriority)
# obj.rmv(taskId)
# param_4 = obj.execTop()


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, val in zip(
            [["TaskManager", "add", "edit", "execTop", "rmv", "add", "execTop"]],
            [[[[1, 101, 10], [2, 102, 20], [3, 103, 15]], [4, 104, 5], [102, 8], [], [101], [5, 105, 15], []]]
        ):
            # /* Example
            #  *  Input:
            #  *  ["TaskManager", "add", "edit", "execTop", "rmv", "add", "execTop"]
            #  *  [[[[1, 101, 10], [2, 102, 20], [3, 103, 15]]], [4, 104, 5], [102, 8], [], [101], [5, 105, 15], []]
            #  *  Output:
            #  *  [null, null, null, 3, null, null, 5]
            #  */
            logging.info("%s", methods)
            logging.info("%s", val)

            displayStr = []
            for key, value in zip(methods, val):
                if key == "TaskManager":
                    obj = TaskManager(value)
                    displayStr.append(None)
                elif key == "add":
                    obj.add(value[0], value[1], value[2])
                    displayStr.append(None)
                elif key == "edit":
                    retVal = obj.edit(value[0], value[1])
                    displayStr.append(None)
                elif key == "execTop":
                    retVal = obj.execTop()
                    displayStr.append(retVal)
                elif key == "rmv":
                    retVal = obj.rmv(value[0])
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

        print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

        sys.exit(0)
