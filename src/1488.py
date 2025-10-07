import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop

from sortedcontainers import SortedList


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
    def avoidFlood(self, rains: List[int]) -> List[int]:
        retVal = []

        rainsSize = len(rains)
        retVal = [1] * rainsSize

        st = SortedList()
        mp = {}
        for i, rain in enumerate(rains):
            if rain == 0:
                st.add(i)
                continue

            retVal[i] = -1
            if rain in mp:
                it = st.bisect(mp[rain])
                if it == len(st):
                    retVal = []
                    break
                retVal[st[it]] = rain
                st.discard(st[it])
            mp[rain] = i

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for rains in [[1, 2, 3, 4], [1, 2, 0, 0, 2, 1], [1, 2, 0, 1, 2]]:
            # /* Example
            #  *  Input: rains = [1,2,3,4]
            #  *  Output: [-1,-1,-1,-1]
            #  *
            #  *  Input: rains = [1,2,0,0,2,1]
            #  *  Output: [-1,-1,2,1,-1,-1]
            #  *
            #  *  Input: rains = [1,2,0,1,2]
            #  *  Output: []
            #  */
            logging.info("Input: rains = %s", rains)

            retVal = pSolution.avoidFlood(rains)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
