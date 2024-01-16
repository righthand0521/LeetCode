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
    def canCompleteCircuit(self, gas: List[int], cost: List[int]) -> int:
        retVal = -1

        gasSize = len(gas)

        # /* https://leetcode.cn/problems/gas-station/solutions/488498/shou-hua-tu-jie-liang-ge-guan-jian-jie-lun-de-jian/
        #  *  1. if sum(gas) < sum(cost), then it has no solution(-1).
        #  *  2. if sum(gas) >= sum(cost), then it has solution(i).
        #  *
        #  *      sum(gas) < sum(cost)     sum(gas) >= sum(cost)
        #  *     /                    \   /                     \
        #  *  [0]----------------------[i]-----------------------[n]
        #  */
        tank = 0
        totalSum = 0
        start = 0
        for i in range(gasSize):
            totalSum += (gas[i] - cost[i])
            tank += (gas[i] - cost[i])
            if tank < 0:
                start = i + 1
                tank = 0

        if totalSum >= 0:
            retVal = start

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for gas, cost in zip([[1, 2, 3, 4, 5], [2, 3, 4],], [[3, 4, 5, 1, 2], [3, 4, 3]]):
            # /* Example
            #  *  Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
            #  *  Output: 3
            #  *
            #  *  Input: gas = [2,3,4], cost = [3,4,3]
            #  *  Output: -1
            #  */
            logging.info("Input: gas = %s, cost = %s", gas, cost)

            retVal = pSolution.canCompleteCircuit(gas, cost)
            logging.info("Output: %s", retVal)

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
