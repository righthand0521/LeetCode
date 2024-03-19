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
    def leastInterval(self, tasks: List[str], n: int) -> int:
        retVal = 0

        tasksSize = len(tasks)

        frequency = [0] * 26
        maxFrequency = 0
        for task in tasks:
            idx = ord(task) - ord('A')
            frequency[idx] += 1
            maxFrequency = max(maxFrequency, frequency[idx])

        time = (maxFrequency - 1) * (n + 1)
        for f in frequency:
            if f == maxFrequency:
                time += 1

        retVal = max(tasksSize, time)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for tasks, n in zip([["A", "A", "A", "B", "B", "B"],
                             ["A", "C", "A", "B", "D", "B"],
                             ["A", "A", "A", "B", "B", "B"]],
                            [2, 1, 3]):
            # /* Example
            #  *  Input: tasks = ["A","A","A","B","B","B"], n = 2
            #  *  Output: 8
            #  *
            #  *  Input: tasks = ["A","C","A","B","D","B"], n = 1
            #  *  Output: 6
            #  *
            #  *  Input: tasks = ["A","A","A", "B","B","B"], n = 3
            #  *  Output: 10
            #  */
            logging.info("Input: tasks = %s, n = %s", tasks, n)

            retVal = pSolution.leastInterval(tasks, n)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass

    sys.exit(0)
