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
    def longestCommonPrefix(self, strs: List[str]) -> str:
        retVal = ""

        retVal = strs[0]  # 1 <= strs.length <= 200
        retValLength = len(retVal)
        strsSize = len(strs)
        for i in range(1, strsSize):
            for j in range(retValLength):
                if (j == len(strs[i])) or (retVal[j] != strs[i][j]):
                    retValLength = j
                    break
        retVal = retVal[:retValLength]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for strs in [["flower", "flow", "flight"], ["dog", "racecar", "car"]]:
            # /* Example
            #  *  Input: strs = ["flower","flow","flight"]
            #  *  Output: "fl"
            #  *
            #  *  Input: strs = ["dog","racecar","car"]
            #  *  Output: ""
            #  */
            logging.info("Input: strs = %s", strs)

            retVal = pSolution.longestCommonPrefix(strs)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
