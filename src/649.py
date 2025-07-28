import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop
from copy import deepcopy


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
    def predictPartyVictory(self, senate: str) -> str:
        retVal = ""

        queueRadiant = deque()
        queueDire = deque()

        senateSize = len(senate)
        for i in range(senateSize):
            if senate[i] == 'R':
                queueRadiant.append(i)
            elif senate[i] == 'D':
                queueDire.append(i)

        while queueRadiant and queueDire:
            idxRadiant = queueRadiant.popleft()
            idxDire = queueDire.popleft()
            if idxRadiant < idxDire:
                queueRadiant.append(idxRadiant + senateSize)
            elif idxRadiant > idxDire:
                queueDire.append(idxDire + senateSize)

        if queueRadiant:
            retVal = "Radiant"
        elif queueDire:
            retVal = "Dire"

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for senate in ["RD", "RDD"]:
            # /* Example
            #  *  Input: senate = "RD"
            #  *  Output: "Radiant"
            #  *
            #  *  Input: senate = "RDD"
            #  *  Output: "Dire"
            #  */
            logging.info("Input: senate = \"%s\"", senate)

            retVal = pSolution.predictPartyVictory(senate)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
