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
    def maximumInvitations(self, favorite: List[int]) -> int:
        retVal = 0

        favoriteSize = len(favorite)

        # Calculate in-degree for each node
        inDegree = [0] * favoriteSize
        for person in range(favoriteSize):
            inDegree[favorite[person]] += 1

        # Topological sorting to remove non-cycle nodes
        TopologicalSortingQueue = deque()
        for person in range(favoriteSize):
            if inDegree[person] == 0:
                TopologicalSortingQueue.append(person)

        depth = [1] * favoriteSize  # Depth of each node

        while TopologicalSortingQueue:
            currentNode = TopologicalSortingQueue.popleft()
            nextNode = favorite[currentNode]
            depth[nextNode] = max(depth[nextNode], depth[currentNode] + 1)
            inDegree[nextNode] -= 1
            if inDegree[nextNode] == 0:
                TopologicalSortingQueue.append(nextNode)

        # Detect cycles
        longestCycle = 0
        twoCycleInvitations = 0
        for person in range(favoriteSize):
            if inDegree[person] == 0:  # Already processed
                continue

            cycleLength = 0
            current = person
            while inDegree[current] != 0:
                inDegree[current] = 0  # Mark as visited
                cycleLength += 1
                current = favorite[current]

            if cycleLength == 2:  # For 2-cycles, add the depth of both nodes
                twoCycleInvitations += depth[person] + depth[favorite[person]]
            else:
                longestCycle = max(longestCycle, cycleLength)

        retVal = max(longestCycle, twoCycleInvitations)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for favorite in [[2, 2, 1, 2], [1, 2, 0], [3, 0, 1, 4, 1]]:
            # /* Example
            #  *  Input: favorite = [2,2,1,2]
            #  *  Output: 3
            #  *
            #  *  Input: favorite = [1,2,0]
            #  *  Output: 3
            #  *
            #  *  Input: favorite = [3,0,1,4,1]
            #  *  Output: 4
            #  */
            logging.info("Input: favorite = %s", favorite)

            retVal = pSolution.maximumInvitations(favorite)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
