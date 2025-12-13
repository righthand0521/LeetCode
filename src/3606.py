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
    def check(self, code: str, isActive: bool) -> bool:
        retVal = False

        if not code:
            return retVal

        for char in code:
            if (char != '_') and (not char.isalnum()):
                return retVal

        retVal = isActive

        return retVal

    def validateCoupons(self, code: List[str], businessLine: List[str], isActive: List[bool]) -> List[str]:
        retVal = []

        businessMapping = {
            "electronics": 0,
            "grocery": 1,
            "pharmacy": 2,
            "restaurant": 3
        }

        groups = [[] for _ in range(4)]
        codeSize = len(code)
        for i in range(codeSize):
            if not code[i]:
                continue
            elif self.check(code[i], isActive[i]) is False:
                continue

            business = businessLine[i]
            if business in businessMapping:
                groups[businessMapping[business]].append(code[i])

        for group in groups:
            group.sort()
            retVal.extend(group)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for code, businessLine, isActive in [
                [
                    ["SAVE20", "", "PHARMA5", "SAVE@20"],
                    ["restaurant", "grocery", "pharmacy", "restaurant"],
                    [True, True, True, True]
                ],
                [
                    ["GROCERY15", "ELECTRONICS_50", "DISCOUNT10"],
                    ["grocery", "electronics", "invalid"],
                    [False, True, True]
                ]
        ]:
            # /* Example
            #  *  Input: code = ["SAVE20","","PHARMA5","SAVE@20"],
            #  *         businessLine = ["restaurant","grocery","pharmacy","restaurant"],
            #  *         isActive = [true,true,true,true]
            #  *  Output: ["PHARMA5","SAVE20"]
            #  *
            #  *  Input: code = ["GROCERY15","ELECTRONICS_50","DISCOUNT10"],
            #  *         businessLine = ["grocery","electronics","invalid"],
            #  *         isActive = [false,true,true]
            #  *  Output: ["ELECTRONICS_50"]
            #  */
            logging.info("Input: code = %s, businessLine = %s, isActive = %s", code, businessLine, isActive)

            retVal = pSolution.validateCoupons(code, businessLine, isActive)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
