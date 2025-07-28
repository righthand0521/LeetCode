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
    def bfs(self, rooms: List[List[int]], enterRoomNumber: int) -> int:
        retVal = 0

        roomsSize = len(rooms)
        visitedRoom = [False] * roomsSize

        bfsQueue = deque([enterRoomNumber])
        visitedRoom[enterRoomNumber] = True
        retVal += 1
        while bfsQueue:
            idx = bfsQueue.popleft()
            for key in rooms[idx]:
                if visitedRoom[key] == True:
                    continue
                bfsQueue.append(key)
                visitedRoom[key] = True
                retVal += 1

        return retVal

    def canVisitAllRooms(self, rooms: List[List[int]]) -> bool:
        retVal = False

        roomsSize = len(rooms)
        openedRoomCount = self.bfs(rooms, 0)
        if openedRoomCount == roomsSize:
            retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print("")

        pSolution = Solution()
        for rooms in [[[1], [2], [3], []], [[1, 3], [3, 0, 1], [2], [0]]]:
            # /* Example
            #  *  Input: rooms = [[1],[2],[3],[]]
            #  *  Output: true
            #  *
            #  *  Input: rooms = [[1,3],[3,0,1],[2],[0]]
            #  *  Output: false
            #  */
            logging.info("Input: rooms = %s", rooms)

            retVal = pSolution.canVisitAllRooms(rooms)
            logging.info("Output: %s", retVal)

            print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
