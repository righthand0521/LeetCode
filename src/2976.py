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
    def __init__(self) -> None:
        # source, target consist of lowercase English letters.
        # original[i], changed[i] are lowercase English letters.
        self.letters = 26

    def dijkstra(self, startChar: int, adjacencyList: List[List[tuple]]) -> List[int]:
        retVal = [float("inf")] * self.letters

        # Priority queue to store characters with their conversion cost, sorted by cost
        priorityQueue = [(0, startChar)]
        while priorityQueue:
            currentCost, currentChar = heappop(priorityQueue)

            if retVal[currentChar] != float("inf"):
                continue
            retVal[currentChar] = currentCost

            # Explore all possible conversions from the current character
            for targetChar, conversionCost in adjacencyList[currentChar]:
                newTotalCost = currentCost + conversionCost

                # If we found a cheaper conversion, update its cost
                if retVal[targetChar] == float("inf"):
                    heappush(priorityQueue, (newTotalCost, targetChar))

        return retVal

    def minimumCost(self, source: str, target: str, original: List[str], changed: List[str], cost: List[int]) -> int:
        retVal = 0

        adjacencyList = [[] for _ in range(self.letters)]
        originalSize = len(original)
        for i in range(originalSize):
            originalIdx = ord(original[i]) - ord("a")
            changedIdx = ord(changed[i]) - ord("a")
            adjacencyList[originalIdx].append((changedIdx, cost[i]))

        # Calculate shortest paths for all possible character conversions
        minConversionCosts = []
        for i in range(self.letters):
            minCost = self.dijkstra(i, adjacencyList)
            minConversionCosts.append(minCost)

        # Calculate the total cost of converting source to target
        for s, t in zip(source, target):
            if s == t:
                continue

            sIdx = ord(s) - ord("a")
            tIdx = ord(t) - ord("a")
            charConversionCost = minConversionCosts[sIdx][tIdx]
            if charConversionCost == float("inf"):
                # If it is impossible to convert source to target, return -1.
                retVal = -1
                return retVal
            retVal += charConversionCost

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for source, target, original, changed, cost in zip(
            ["abcd", "aaaa", "abcd"],
            ["acbe", "bbbb", "abce"],
            [["a", "b", "c", "c", "e", "d"], ["a", "c"], ["a"]],
            [["b", "c", "b", "e", "b", "e"], ["c", "b"], ["e"]],
            [[2, 5, 5, 1, 2, 20], [1, 2], [10000]]
        ):
            # /* Example
            #  *  Input: source = "abcd", target = "acbe",
            #  *  original = ["a","b","c","c","e","d"], changed = ["b","c","b","e","b","e"], cost = [2,5,5,1,2,20]
            #  *  Output: 28
            #  *
            #  *  Input: source = "aaaa", target = "bbbb", original = ["a","c"], changed = ["c","b"], cost = [1,2]
            #  *  Output: 12
            #  *
            #  *  Input: source = "abcd", target = "abce", original = ["a"], changed = ["e"], cost = [10000]
            #  *  Output: -1
            #  */
            logging.info("Input: source = \"%s\", target = \"%s\", original = %s, changed = %s, cost = %s",
                         source, target, original, changed, cost)

            retVal = pSolution.minimumCost(source, target, original, changed, cost)
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
