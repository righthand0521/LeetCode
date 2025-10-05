import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from typing import List, Optional, Tuple, Set


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
    def bfs(self, heights: List[List[int]], starts: List[Tuple[int, int]]) -> Set[Tuple[int, int]]:
        retVal = None

        heightsSize = len(heights)
        heightsColSize = len(heights[0])

        bfsQueue = deque(starts)
        visited = set(starts)
        while bfsQueue:
            x, y = bfsQueue.popleft()
            for nx, ny in ((x, y + 1), (x, y - 1), (x - 1, y), (x + 1, y)):
                if (nx < 0) or (nx >= heightsSize) or (ny < 0) or (ny >= heightsColSize):
                    continue
                elif (nx, ny) in visited:
                    continue

                if heights[nx][ny] >= heights[x][y]:
                    bfsQueue.append((nx, ny))
                    visited.add((nx, ny))
        retVal = visited

        return retVal

    def pacificAtlantic(self, heights: List[List[int]]) -> List[List[int]]:
        retVal = []

        heightsSize = len(heights)
        heightsColSize = len(heights[0])

        pacific = [(0, i) for i in range(heightsColSize)]
        pacific += [(i, 0) for i in range(1, heightsSize)]
        atlantic = [(heightsSize - 1, i) for i in range(heightsColSize)]
        atlantic += [(i, heightsColSize - 1) for i in range(heightsSize - 1)]
        retVal = list(map(list, self.bfs(heights, pacific) & self.bfs(heights, atlantic)))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for heights in [[[1, 2, 2, 3, 5], [3, 2, 3, 4, 4], [2, 4, 5, 3, 1], [6, 7, 1, 4, 5], [5, 1, 1, 2, 4]], [[1]]]:
            # /* Example
            #  *  Input: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
            #  *  Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
            #  *
            #  *  Input: heights = [[1]]
            #  *  Output: [[0,0]]
            #  */
            logging.info("Input: heights = %s", heights)

            retVal = pSolution.pacificAtlantic(heights)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
