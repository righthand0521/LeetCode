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
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        retVal = []

        hashTable = defaultdict(list)
        for str in strs:
            key = "".join(sorted(str))
            hashTable[key].append(str)
        retVal = list(hashTable.values())

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for strs in [["eat", "tea", "tan", "ate", "nat", "bat"], [""], ["a"]]:
            # /* Example
            #  *  Input: strs = ["eat","tea","tan","ate","nat","bat"]
            #  *  Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
            #  *
            #  *  Input: strs = [""]
            #  *  Output: [[""]]
            #  *
            #  *  Input: strs = ["a"]
            #  *  Output: [["a"]]
            #  */
            logging.info("Input: strs = '%s'", strs)

            retVal = pSolution.groupAnagrams(strs)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
