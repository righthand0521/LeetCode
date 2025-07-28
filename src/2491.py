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
    def dividePlayers(self, skill: List[int]) -> int:
        retVal = -1

        skillSize = len(skill)

        totalSkill = sum(skill)
        if totalSkill % (skillSize // 2) != 0:
            return retVal

        skillFrequency = [0] * 1001  # // 1 <= skill[i] <= 1000
        for playerSkill in skill:
            skillFrequency[playerSkill] += 1

        targetTeamSkill = totalSkill // (skillSize // 2)
        totalChemistry = 0
        for playerSkill in skill:
            partnerSkill = targetTeamSkill - playerSkill
            if skillFrequency[partnerSkill] == 0:
                return retVal

            totalChemistry += (playerSkill * partnerSkill)
            skillFrequency[partnerSkill] -= 1

        retVal = totalChemistry // 2

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for skill in [[3, 2, 5, 1, 3, 4], [3, 4], [1, 1, 2, 3]]:
            # /* Example
            #  *  Input: skill = [3,2,5,1,3,4]
            #  *  Output: 22
            #  *
            #  *  Input: skill = [3,4]
            #  *  Output: 12
            #  *
            #  *  Input: skill = [1,1,2,3]
            #  *  Output: -1
            #  */
            logging.info("Input: skill = %s", skill)

            retVal = pSolution.dividePlayers(skill)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
