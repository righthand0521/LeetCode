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
    def countMentions(self, numberOfUsers: int, events: List[List[str]]) -> List[int]:
        retVal = [0] * numberOfUsers

        nextOnlineTime = [0] * numberOfUsers
        events.sort(key=lambda e: (int(e[1]), e[0] == "MESSAGE"))
        for event in events:
            curTime = int(event[1])

            if event[0] == "MESSAGE":
                if event[2] == "ALL":
                    for i in range(numberOfUsers):
                        retVal[i] += 1
                elif event[2] == "HERE":
                    for i, t in enumerate(nextOnlineTime):
                        if t <= curTime:
                            retVal[i] += 1
                else:
                    for idx in event[2].split():
                        retVal[int(idx[2:])] += 1
            else:
                nextOnlineTime[int(event[2])] = curTime + 60

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for numberOfUsers, events in [
                [2, [["MESSAGE", "10", "id1 id0"], ["OFFLINE", "11", "0"], ["MESSAGE", "71", "HERE"]]],
                [2, [["MESSAGE", "10", "id1 id0"], ["OFFLINE", "11", "0"], ["MESSAGE", "12", "ALL"]]],
                [2, [["OFFLINE", "10", "0"], ["MESSAGE", "12", "HERE"]]]
        ]:
            # /* Example
            #  *  Input: numberOfUsers = 2, events = [["MESSAGE","10","id1 id0"],["OFFLINE","11","0"],["MESSAGE","71","HERE"]]
            #  *  Output: [2,2]
            #  *
            #  *  Input: numberOfUsers = 2, events = [["MESSAGE","10","id1 id0"],["OFFLINE","11","0"],["MESSAGE","12","ALL"]]
            #  *  Output: [2,2]
            #  *
            #  *  Input: numberOfUsers = 2, events = [["OFFLINE","10","0"],["MESSAGE","12","HERE"]]
            #  *  Output: [0,1]
            #  */
            logging.info("Input: numberOfUsers = %s, events = %s", numberOfUsers, events)

            retVal = pSolution.countMentions(numberOfUsers, events)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
