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
    def validArrangement(self, pairs: List[List[int]]) -> List[List[int]]:
        retVal = []

        # Build the adjacency list and track in-degrees and out-degrees
        adjacencyMatrix = defaultdict(list)
        inDegree = defaultdict(int)
        outDegree = defaultdict(int)
        for start, end in pairs:
            adjacencyMatrix[start].append(end)
            outDegree[start] += 1
            inDegree[end] += 1

        # Find the start node (outDegree == inDegree + 1)
        startNode = -1
        for node in outDegree:
            if outDegree[node] == inDegree[node] + 1:
                startNode = node
                break
        if startNode == -1:  # If no such node exists, start from the first pair's first element
            startNode = pairs[0][0]

        result = []
        # Iterative DFS using stack
        nodeStack = [startNode]
        while nodeStack:
            node = nodeStack[-1]
            if adjacencyMatrix[node]:  # Visit the next node
                nextNode = adjacencyMatrix[node].pop(0)
                nodeStack.append(nextNode)
            else:  # No more neighbors to visit, add node to result
                result.append(node)
                nodeStack.pop()
        result.reverse()  # Reverse the result since we collected nodes in reverse order

        # Construct the result pairs
        for i in range(1, len(result)):
            retVal.append([result[i - 1], result[i]])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for pairs in [[[5, 1], [4, 5], [11, 9], [9, 4]], [[1, 3], [3, 2], [2, 1]], [[1, 2], [1, 3], [2, 1]]]:
            # /* Example
            #  *  Input: pairs = [[5,1],[4,5],[11,9],[9,4]]
            #  *  Output: [[11,9],[9,4],[4,5],[5,1]]
            #  *
            #  *  Input: pairs = [[1,3],[3,2],[2,1]]
            #  *  Output: [[1,3],[3,2],[2,1]]
            #  *
            #  *  Input: pairs = [[1,2],[1,3],[2,1]]
            #  *  Output: [[1,2],[2,1],[1,3]]
            #  */
            logging.info("Input: pairs = %s", pairs)

            retVal = pSolution.validArrangement(pairs)
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
