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
    def matchPlayersAndTrainers(self, players: List[int], trainers: List[int]) -> int:
        retVal = 0

        players.sort()
        playersSize = len(players)
        playersIdx = 0

        trainers.sort()
        trainersSize = len(trainers)
        trainersIdx = 0

        while (playersIdx < playersSize) and (trainersIdx < trainersSize):
            while (trainersIdx < trainersSize) and (players[playersIdx] > trainers[trainersIdx]):
                trainersIdx += 1
            retVal += 1 if trainersIdx < trainersSize else 0
            playersIdx += 1
            trainersIdx += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for players, trainers in zip([[4, 7, 9], [1, 1, 1]], [[8, 2, 5, 8], [10]]):
            # /* Example
            #  *  Input: players = [4,7,9], trainers = [8,2,5,8]
            #  *  Output: 2
            #  *
            #  *  Input: players = [1,1,1], trainers = [10]
            #  *  Output: 1
            #  */
            logging.info("Input: players = %s, trainers = %s",
                         players, trainers)

            retVal = pSolution.matchPlayersAndTrainers(players, trainers)
            logging.info("Output: %d", retVal)

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
