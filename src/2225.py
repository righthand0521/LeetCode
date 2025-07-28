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
    def findWinners(self, matches: List[List[int]]) -> List[List[int]]:
        retVal = []

        winHashTable = defaultdict(int)
        lostHashTable = defaultdict(int)
        for win, lost in matches:
            winHashTable[win] += 1
            lostHashTable[lost] += 1

        lostExactlyOne = []
        for i in lostHashTable:
            if lostHashTable[i] == 1:
                lostExactlyOne.append(i)
        lostExactlyOne.sort()

        notLost = []
        for i in winHashTable:
            if i not in lostHashTable:
                notLost.append(i)
        notLost.sort()

        retVal = [notLost, lostExactlyOne]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for matches in [[[1, 3], [2, 3], [3, 6], [5, 6], [5, 7], [4, 5], [4, 8], [4, 9], [10, 4], [10, 9]],
                        [[2, 3], [1, 3], [5, 4], [6, 4]]]:
            # /* Example
            #  *  Input: matches = [[1,3],[2,3],[3,6],[5,6],[5,7],[4,5],[4,8],[4,9],[10,4],[10,9]]
            #  *  Output: [[1,2,10],[4,5,7,8]]
            #  *
            #  *  Input: matches = [[2,3],[1,3],[5,4],[6,4]]
            #  *  Output: [[1,2,5,6],[]]
            #  */
            logging.info("Input: matches = %s", matches)

            retVal = pSolution.findWinners(matches)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
