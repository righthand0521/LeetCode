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


class Solution:
    def check(self, tasks: List[int], workers: List[int], pills: int, strength: int, middle: int) -> bool:
        retVal = False

        workersSize = len(workers)
        workersIdx = workersSize - 1
        workersQueue = deque()
        for i in range(middle - 1, -1, -1):
            while (workersIdx >= workersSize - middle) and (workers[workersIdx] + strength >= tasks[i]):
                workersQueue.appendleft(workers[workersIdx])
                workersIdx -= 1
            if not workersQueue:
                return retVal

            # If the largest element in the deque is greater than or equal to tasks[i]
            if workersQueue[-1] >= tasks[i]:
                workersQueue.pop()
                continue

            if pills == 0:
                return retVal

            pills -= 1
            workersQueue.popleft()

        retVal = True

        return retVal

    def maxTaskAssign(self, tasks: List[int], workers: List[int], pills: int, strength: int) -> int:
        retVal = 0

        tasksSize = len(tasks)
        tasks.sort()

        workersSize = len(workers)
        workers.sort()

        left = 1
        right = min(workersSize, tasksSize)
        while left <= right:
            middle = (left + right) // 2
            if self.check(tasks, workers, pills, strength, middle) == True:
                left = middle + 1
                retVal = middle
            else:
                right = middle - 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for tasks, workers, pills, strength in zip(
                [[3, 2, 1], [5, 4], [10, 15, 30]],
                [[0, 3, 3], [0, 0, 0], [0, 10, 10, 10, 10]],
                [1, 1, 3],
                [1, 5, 10]
        ):
            # /* Example
            #  *  Input: tasks = [3,2,1], workers = [0,3,3], pills = 1, strength = 1
            #  *  Output: 3
            #  *
            #  *  Input: tasks = [5,4], workers = [0,0,0], pills = 1, strength = 5
            #  *  Output: 1
            #  *
            #  *  Input: tasks = [10,15,30], workers = [0,10,10,10,10], pills = 3, strength = 10
            #  *  Output: 2
            #  */
            logging.info("Input: tasks = %s, workers = %s, pills = %s, strength = %s", tasks, workers, pills, strength)

            retVal = pSolution.maxTaskAssign(tasks, workers, pills, strength)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
