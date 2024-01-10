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

# /*  括号。
#  *  設計一種算法，打印n對括號的所有合法的（例如，開閉一一對應）組合。
#  *      說明：解集不能包含重複的子集。
#  *      例如，給出 n = 3，生成結果為：
#  *      [
#  *          "((()))",
#  *          "(()())",
#  *          "(())()",
#  *          "()(())",
#  *          "()()()"
#  *      ]
#  */


class Solution:
    def backtracking(self, retVal: List[str], str: str, open: int, close: int):
        if open == 0 and close == 0:
            retVal.append(str)

        if open > 0:
            self.backtracking(retVal, str + "(", open - 1, close)

        if close > open:
            self.backtracking(retVal, str + ")", open, close-1)

    def generateParenthesis(self, n: int) -> List[str]:
        retVal = []

        self.backtracking(retVal, "", n, n)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [3, 1]:
            # /* Example
            #  *  Input: n = 3
            #  *  Output: ["((()))","(()())","(())()","()(())","()()()"]
            #  *
            #  *  Input: n = 1
            #  *  Output: ["()"]
            #  */
            logging.info("Input: n = %s", n)

            retVal = pSolution.generateParenthesis(n)
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
