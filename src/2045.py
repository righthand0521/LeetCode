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


class Solution:
    def secondMinimum(self, n: int, edges: List[List[int]], time: int, change: int) -> int:
        retVal = 0

        #
        adjacencyList = [[] for _ in range(n + 1)]
        for start, end in edges:
            adjacencyList[start].append(end)
            adjacencyList[end].append(start)

        #
        bfsQueue = deque()
        bfsQueue.append((1, 1))

        dist1 = [-1] * (n + 1)
        dist1[1] = 0

        dist2 = [-1] * (n + 1)

        #
        while bfsQueue:
            node, frequency = bfsQueue.popleft()

            # If the timeTaken falls under the red bracket, wait till the path turns green.
            timeTaken = dist1[node] if frequency == 1 else dist2[node]
            if (timeTaken // change) % 2:
                timeTaken = change * (timeTaken // change + 1) + time
            else:
                timeTaken = timeTaken + time

            for neighbor in adjacencyList[node]:
                if dist1[neighbor] == -1:
                    dist1[neighbor] = timeTaken
                    bfsQueue.append((neighbor, 1))
                elif (dist2[neighbor] == -1) and (dist1[neighbor] != timeTaken):
                    if neighbor == n:
                        retVal = timeTaken
                        return retVal
                    dist2[neighbor] = timeTaken
                    bfsQueue.append((neighbor, 2))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, edges, time, change in zip([5, 2], [[[1, 2], [1, 3], [1, 4], [3, 4], [4, 5]], [[1, 2]]], [3, 3], [5, 2]):
            # /* Example
            #  *  Input: n = 5, edges = [[1,2],[1,3],[1,4],[3,4],[4,5]], time = 3, change = 5
            #  *  Output: 13
            #  *
            #  *  Input: n = 2, edges = [[1,2]], time = 3, change = 2
            #  *  Output: 11
            #  */
            logging.info("Input: n = %s, edges = %s, time = %s, change = %s", n, edges, time, change)

            retVal = pSolution.secondMinimum(n, edges, time, change)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
