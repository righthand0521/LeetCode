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
    def backtracking(self, candidates: List[int], target: int, start: int, combine: List[int],
                     answer: List[List[int]]) -> None:
        if target == 0:
            answer.append(combine[:])
            return

        candidatesSize = len(candidates)
        for i in range(start, candidatesSize):
            if (i > start) and (candidates[i] == candidates[i - 1]):
                continue

            updateTarget = target - candidates[i]
            if updateTarget < 0:
                break

            combine.append(candidates[i])
            self.backtracking(candidates, updateTarget, i + 1, combine, answer)
            combine.pop()

    def combinationSum2(self, candidates: List[int], target: int) -> List[List[int]]:
        retVal = []

        if not candidates:
            return retVal

        if min(candidates) > target:
            retVal

        candidates.sort()

        combine = []
        self.backtracking(candidates, target, 0, combine, retVal)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for candidates, target in zip([[10, 1, 2, 7, 6, 1, 5], [2, 5, 2, 1, 2]], [8, 5]):
            # /* Example
            #  *  Input: candidates = [10,1,2,7,6,1,5], target = 8
            #  *  Output: [[1,1,6],[1,2,5],[1,7],[2,6]]
            #  *
            #  *  Input: candidates = [2,5,2,1,2], target = 5
            #  *  Output: [[1,2,2],[5]]
            #  */
            logging.info("Input: candidates = %s, target = %s",
                         candidates, target)

            retVal = pSolution.combinationSum2(candidates, target)
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
