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
    def getLongestSubsequence(self, words: List[str], groups: List[int]) -> List[str]:
        retVal = []

        retVal.append(words[0])
        groupsSize = len(groups)
        for i in range(1, groupsSize):
            if groups[i] != groups[i - 1]:
                retVal.append(words[i])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for words, groups in zip([["e", "a", "b"], ["a", "b", "c", "d"]], [[0, 0, 1], [1, 0, 1, 1]]):
            # /* Example
            #  *  Input: words = ["e","a","b"], groups = [0,0,1]
            #  *  Output: ["e","b"]
            #  *
            #  *  Input: words = ["a","b","c","d"], groups = [1,0,1,1]
            #  *  Output: ["a","b","c"]
            #  */
            logging.info("Input: words = %s, groups = %s", words, groups)

            retVal = pSolution.getLongestSubsequence(words, groups)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
