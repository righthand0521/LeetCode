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
    def initializeBaseCases(self, expression: str, dp: List[List[List[int]]]) -> None:
        expressionSize = len(expression)

        for i, char in enumerate(expression):
            if char.isdigit() == False:
                continue

            dig1 = ord(char) - ord("0")
            if (i + 1 < expressionSize) and (expression[i + 1].isdigit()):
                dig2 = ord(expression[i + 1]) - ord("0")
                number = dig1 * 10 + dig2
                dp[i][i + 1].append(number)

            dp[i][i].append(dig1)

    def processSubexpression(self, expression: str, dp: List[List[List[int]]], start: int, end: int) -> None:
        for split in range(start, end + 1):
            if expression[split].isdigit():
                continue

            leftResults = dp[start][split - 1]
            rightResults = dp[split + 1][end]
            self.computeResults(expression[split], leftResults, rightResults, dp[start][end])

    def computeResults(self, op: str, leftResults: List[int], rightResults: List[int], results: List[int]) -> None:
        for leftValue in leftResults:
            for rightValue in rightResults:
                if op == "+":
                    results.append(leftValue + rightValue)
                elif op == "-":
                    results.append(leftValue - rightValue)
                elif op == "*":
                    results.append(leftValue * rightValue)

    def diffWaysToCompute(self, expression: str) -> List[int]:
        retVal = []

        expressionSize = len(expression)
        dp = [[[] for _ in range(expressionSize)] for _ in range(expressionSize)]

        self.initializeBaseCases(expression, dp)

        for length in range(3, expressionSize + 1):
            for start in range(expressionSize - length + 1):
                end = start + length - 1
                self.processSubexpression(expression, dp, start, end)

        retVal = dp[0][expressionSize - 1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for expression in ["2-1-1", "2*3-4*5"]:
            # /* Example
            #  *  Input: expression = "2-1-1"
            #  *  Output: [0,2]
            #  *
            #  *  Input: expression = "2*3-4*5"
            #  *  Output: [-34,-14,-10,-10,10]
            #  */
            logging.info("Input: expression = \"%s\"", expression)

            retVal = pSolution.diffWaysToCompute(expression)
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
