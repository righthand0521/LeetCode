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
    def topologicalSort(self, graph, indegree) -> List[int]:
        retVal = []

        # Tologlogical sort nodes in graph, return [] if a cycle exists.
        visited = []
        stack = [node for node in range(len(graph)) if indegree[node] == 0]
        while stack:
            cur = stack.pop()
            visited.append(cur)
            for neib in graph[cur]:
                indegree[neib] -= 1
                if indegree[neib] == 0:
                    stack.append(neib)

        if len(visited) == len(graph):
            retVal = visited

        return retVal

    def sortItems(self, n: int, m: int, group: List[int], beforeItems: List[List[int]]) -> List[int]:
        retVal = []

        # If an item belongs to zero group, assign it a unique group id.
        group_id = m
        for i in range(n):
            if group[i] == -1:
                group[i] = group_id
                group_id += 1

        # Sort all item regardless of group dependencies.
        item_graph = [[] for _ in range(n)]
        item_indegree = [0] * n

        # Sort all groups regardless of item dependencies.
        group_graph = [[] for _ in range(group_id)]
        group_indegree = [0] * group_id

        for curr in range(n):
            for prev in beforeItems[curr]:
                # Each (prev -> curr) represents an edge in the item graph.
                item_graph[prev].append(curr)
                item_indegree[curr] += 1

                # If they belong to different groups, add an edge in the group graph.
                if group[curr] != group[prev]:
                    group_graph[group[prev]].append(group[curr])
                    group_indegree[group[curr]] += 1

        item_order = self.topologicalSort(item_graph, item_indegree)
        group_order = self.topologicalSort(group_graph, group_indegree)
        if not item_order or not group_order:
            return retVal

        # Items are sorted regardless of groups, we need to differentiate them by the groups they belong to.
        ordered_groups = defaultdict(list)
        for item in item_order:
            ordered_groups[group[item]].append(item)

        # Concatenate sorted items in all sorted groups.
        # [group 1, group 2, ... ] -> [(item 1, item 2, ...), (item 1, item 2, ...), ...]
        for group_index in group_order:
            retVal += ordered_groups[group_index]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, m, group, beforeItems in zip(
            [8, 8], [2, 2], [[-1, -1, 1, 0, 0, 1, 0, -1],
                             [-1, -1, 1, 0, 0, 1, 0, -1]],
                [[[], [6], [5], [6], [3, 6], [], [], []], [[], [6], [5], [6], [3], [], [4], []]]):
            # /* Example
            #  *  Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3,6],[],[],[]]
            #  *  Output: [6,3,4,1,5,2,0,7]
            #  *
            #  *  Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3],[],[4],[]]
            #  *  Output: []
            #  */
            logging.info(
                "Input: n = %s, m = %s, group = %s, beforeItems = %s", n, m, group, beforeItems)

            retVal = pSolution.sortItems(n, m, group, beforeItems)
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
