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
    def __init__(self) -> None:
        self.method = 1

    def backtracking(self, digits: str, retVal: List[str], phoneMap: dict, combination: List[str], index: int) -> None:
        if index == len(digits):
            retVal.append("".join(combination))
            return

        digit = digits[index]
        for letter in phoneMap[digit]:
            combination.append(letter)
            self.backtracking(digits, retVal, phoneMap, combination, index + 1)
            combination.pop()

    def letterCombinations(self, digits: str) -> List[str]:
        retVal = []

        if not digits:
            return retVal

        phoneMap = {
            "2": "abc",
            "3": "def",
            "4": "ghi",
            "5": "jkl",
            "6": "mno",
            "7": "pqrs",
            "8": "tuv",
            "9": "wxyz",
        }

        if self.method == 1:
            combination = list()
            self.backtracking(digits, retVal, phoneMap, combination, 0)
        elif self.method == 2:
            groups = (phoneMap[digit] for digit in digits)
            from itertools import product
            retVal = ["".join(combination) for combination in product(*groups)]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for digits in ["23", "", "2"]:
            # /* Example
            #  *  Input: digits = "23"
            #  *  Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
            #  *
            #  *  Input: digits = ""
            #  *  Output: []
            #  *
            #  *  Input: digits = "2"
            #  *  Output: ["a","b","c"]
            #  */
            logging.info("Input: digits = \"%s\"", digits)

            retVal = pSolution.letterCombinations(digits)
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
