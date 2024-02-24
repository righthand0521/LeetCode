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
    def findAllPeople(self, n: int, meetings: List[List[int]], firstPerson: int) -> List[int]:
        retVal = []

        #
        graph = defaultdict(list)
        for x, y, t in meetings:
            graph[x].append((t, y))
            graph[y].append((t, x))

        #
        secretDefaultValue = float('inf')
        secret = [secretDefaultValue] * n
        secret[0] = 0
        secret[firstPerson] = 0

        #
        bfsQueue = deque()
        bfsQueue.append((0, 0))
        bfsQueue.append((firstPerson, 0))
        while bfsQueue:
            person, time = bfsQueue.popleft()
            for t, nextPerson in graph[person]:
                if t >= time and secret[nextPerson] > t:
                    secret[nextPerson] = t
                    bfsQueue.append((nextPerson, t))

        #
        for i in range(n):
            if secret[i] != secretDefaultValue:
                retVal.append(i)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, meetings, firstPerson in zip([6, 4, 5],
                                            [[[1, 2, 5], [2, 3, 8], [1, 5, 10]],
                                             [[3, 1, 3], [1, 2, 2], [0, 3, 3]],
                                             [[3, 4, 2], [1, 2, 1], [2, 3, 1]]],
                                            [1, 3, 1]):
            # /* Example
            #  *  Input: n = 6, meetings = [[1,2,5],[2,3,8],[1,5,10]], firstPerson = 1
            #  *  Output: [0,1,2,3,5]
            #  *
            #  *  Input: n = 4, meetings = [[3,1,3],[1,2,2],[0,3,3]], firstPerson = 3
            #  *  Output: [0,1,3]
            #  *
            #  *  Input: n = 5, meetings = [[3,4,2],[1,2,1],[2,3,1]], firstPerson = 1
            #  *  Output: [0,1,2,3,4]
            #  */
            logging.info(
                "Input: n = %s, meetings = %s, firstPerson = %s", n, meetings, firstPerson)

            retVal = pSolution.findAllPeople(n, meetings, firstPerson)
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
