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


class Trie:
    serial: str = ""  # current node structure's serialized representation
    children: dict  # current node's child nodes

    def __init__(self):
        self.children = dict()


class Solution:
    # post-order traversal based on depth-first search, calculate the serialized representation of each node structure
    def construct(self, node: Trie, frequency: Counter) -> None:
        # if it is a leaf node, then the serialization is represented as an empty string, and no operation is required.
        if not node.children:
            return

        # if it is not a leaf node, the serialization representation of the child node structure needs to be calculated first.
        v = list()
        for folder, child in node.children.items():
            self.construct(child, frequency)
            v.append(folder + "(" + child.serial + ")")

        # to prevent issues with order, sorting is needed
        v.sort()
        node.serial = "".join(v)

        # add to hash table
        frequency[node.serial] += 1

    def operate(self, node: Trie, frequency: Counter, path: List[str], retVal: List[List[str]]) -> None:
        # if the serialization appears more than once in the hash table, it needs to be deleted.
        if frequency[node.serial] > 1:
            return

        # otherwise add the path to the answer
        if path:
            retVal.append(path[:])

        for folder, child in node.children.items():
            path.append(folder)
            self.operate(child, frequency, path, retVal)
            path.pop()

    def deleteDuplicateFolder(self, paths: List[List[str]]) -> List[List[str]]:
        retVal = []

        # root node
        root = Trie()
        for path in paths:
            current = root
            for node in path:
                if node not in current.children:
                    current.children[node] = Trie()
                current = current.children[node]

        # hash table records the occurrence times of each serialized representation
        frequency = Counter()

        self.construct(root, frequency)

        path = list()  # record the path from the root node to the current node.
        self.operate(root, frequency, path, retVal)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for paths in [
            [["a"], ["c"], ["d"], ["a", "b"], ["c", "b"], ["d", "a"]],
            [["a"], ["c"], ["a", "b"], ["c", "b"], ["a", "b", "x"], ["a", "b", "x", "y"], ["w"], ["w", "y"]],
            [["a", "b"], ["c", "d"], ["c"], ["a"]]
        ]:
            # /* Example
            #  *  Input: paths = [["a"],["c"],["d"],["a","b"],["c","b"],["d","a"]]
            #  *  Output: [["d"],["d","a"]]
            #  *
            #  *  Input: paths = [["a"],["c"],["a","b"],["c","b"],["a","b","x"],["a","b","x","y"],["w"],["w","y"]]
            #  *  Output: [["c"],["c","b"],["a"],["a","b"]]
            #  *
            #  *  Input: paths = [["a","b"],["c","d"],["c"],["a"]]
            #  *  Output: [["c"],["c","d"],["a"],["a","b"]]
            #  */
            logging.info("Input: paths = %s", paths)

            retVal = pSolution.deleteDuplicateFolder(paths)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
