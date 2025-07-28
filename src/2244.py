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
    def minimumRounds(self, tasks: List[int]) -> int:
        retVal = 0

        tasks.sort()

        tasksSize = len(tasks)
        count = 1
        for i in range(1, tasksSize):
            if tasks[i] == tasks[i-1]:
                count += 1
                continue

            if count == 1:
                retVal = -1
                return retVal
            retVal += (count // 3)
            retVal += 0 if count % 3 == 0 else 1

            count = 1

        if count == 1:
            retVal = -1
            return retVal
        retVal += (count // 3)
        retVal += 0 if count % 3 == 0 else 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for tasks in [[2, 2, 3, 3, 2, 4, 4, 4, 4, 4], [2, 3, 3]]:
            # /* Example
            #  *  Input: tasks = [2,2,3,3,2,4,4,4,4,4]
            #  *  Output: 4
            #  *
            #  *  Input: tasks = [2,3,3]
            #  *  Output: -1
            #  */
            logging.info("Input: tasks = %s", tasks)

            retVal = pSolution.minimumRounds(tasks)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
