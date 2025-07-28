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
    def addSpaces(self, s: str, spaces: List[int]) -> str:
        retVal = ""

        sSize = len(s)
        spacesSize = len(spaces)

        sIdx = 0
        spacesIdx = 0
        while sIdx < sSize:
            if (spacesIdx < spacesSize) and (sIdx == spaces[spacesIdx]):
                retVal += ' '
                spacesIdx += 1
                continue
            retVal += s[sIdx]
            sIdx += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, space in zip(["LeetcodeHelpsMeLearn", "icodeinpython", "spacing"],
                            [[8, 13, 15], [1, 5, 7, 9], [0, 1, 2, 3, 4, 5, 6]]):
            # /* Example
            #  *  Input: s = "LeetcodeHelpsMeLearn", spaces = [8,13,15]
            #  *  Output: "Leetcode Helps Me Learn"
            #  *
            #  *  Input: s = "icodeinpython", spaces = [1,5,7,9]
            #  *  Output: "i code in py thon"
            #  *
            #  *  Input: s = "spacing", spaces = [0,1,2,3,4,5,6]
            #  *  Output: " s p a c i n g"
            #  */
            logging.info("Input: s = \"%s\", spaces = %s", s, space)

            retVal = pSolution.addSpaces(s, space)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
