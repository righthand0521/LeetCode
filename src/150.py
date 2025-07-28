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
    def evalRPN(self, tokens: List[str]) -> int:
        retVal = 0

        stack = []
        for token in tokens:
            # tokens[i] is either an operator: "+", "-", "*", or "/"
            if (token == "+") or (token == "-") or (token == "*") or (token == "/"):
                if token == "+":
                    value = stack[-2] + stack[-1]
                elif token == "-":
                    value = stack[-2] - stack[-1]
                elif token == "*":
                    value = stack[-2] * stack[-1]
                elif token == "/":
                    value = stack[-2] / stack[-1]

                stack.pop()
                stack.pop()
                stack.append(int(value))
            else:
                stack.append(int(token))

        retVal = stack[0]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for tokens in [
            ["2", "1", "+", "3", "*"],
            ["4", "13", "5", "/", "+"],
            ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"]
        ]:
            # /* Example
            #  *  Input: tokens = ["2","1","+","3","*"]
            #  *  Output: 9
            #  *
            #  *  Input: tokens = ["4","13","5","/","+"]
            #  *  Output: 6
            #  *
            #  *  Input: tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
            #  *  Output: 22
            #  */
            logging.info("Input: tokens = %s", tokens)

            retVal = pSolution.evalRPN(tokens)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
