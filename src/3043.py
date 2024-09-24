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


class TrieNode:
    def __init__(self):
        # Each node has up to 10 possible children (digits 0-9)
        self.children = [None] * 10


class Trie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, num) -> None:
        node = self.root
        numStr = str(num)
        for digit in numStr:
            idx = int(digit)
            if not node.children[idx]:
                node.children[idx] = TrieNode()
            node = node.children[idx]

    def findLongestPrefix(self, num) -> int:
        retVal = 0

        node = self.root
        numStr = str(num)
        for digit in numStr:
            idx = int(digit)
            if node.children[idx]:
                # Increase length if the current digit matches
                retVal += 1
                node = node.children[idx]
            else:
                # Stop if no match for the current digit
                break

        return retVal


class Solution:
    def longestCommonPrefix(self, arr1: List[int], arr2: List[int]) -> int:
        retVal = 0

        trie = Trie()

        # Step 1: Insert all numbers from arr1 into the Trie
        for num in arr1:
            trie.insert(num)

        # Step 2: Find the longest prefix match for each number in arr2
        for num in arr2:
            len = trie.findLongestPrefix(num)
            retVal = max(retVal, len)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr1, arr2 in zip([[1, 10, 100], [1, 2, 3]], [[1000], [4, 4, 4]]):
            # /* Example
            #  *  Input: arr1 = [1,10,100], arr2 = [1000]
            #  *  Output: 3
            #  *
            #  *  Input: arr1 = [1,2,3], arr2 = [4,4,4]
            #  *  Output: 0
            #  */
            logging.info("Input: arr1 = %s, arr2 = %s", arr1, arr2)

            retVal = pSolution.longestCommonPrefix(arr1, arr2)
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
