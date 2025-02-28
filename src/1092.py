import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from math import gcd
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
    def shortestCommonSupersequence(self, str1: str, str2: str) -> str:
        retVal = ""

        str1Size = len(str1)
        str2Size = len(str2)

        # Initialize the base cases
        dp = [[0 for _ in range(str2Size + 1)] for _ in range(str1Size + 1)]
        # When str2 is empty, the supersequence is str1 itself (length = row index)
        for row in range(str1Size + 1):
            dp[row][0] = row
        # When str1 is empty, the supersequence is str2 itself (length = col index)
        for col in range(str2Size + 1):
            dp[0][col] = col

        for row in range(1, str1Size + 1):
            for col in range(1, str2Size + 1):
                if str1[row - 1] == str2[col - 1]:  # If characters match, inherit the length from the diagonal +1
                    dp[row][col] = dp[row - 1][col - 1] + 1
                else:  # If characters do not match, take the minimum length option +1
                    dp[row][col] = min(dp[row - 1][col], dp[row][col - 1]) + 1

        row = str1Size
        col = str2Size
        while row > 0 and col > 0:
            if str1[row - 1] == str2[col - 1]:  # If characters match, take it from diagonal
                retVal += str1[row - 1]
                row -= 1
                col -= 1
            elif dp[row - 1][col] < dp[row][col - 1]:  # If str1’s character is part of the supersequence, move up
                retVal += str1[row - 1]
                row -= 1
            else:  # If str2’s character is part of the supersequence, move left
                retVal += str2[col - 1]
                col -= 1

        # Append any remaining characters if there are leftover characters in str1
        while row > 0:
            retVal += str1[row - 1]
            row -= 1
        # If there are leftover characters in str2
        while col > 0:
            retVal += str2[col - 1]
            col -= 1
        # Reverse the built sequence to get the correct order
        retVal = retVal[::-1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for str1, str2 in zip(["abac", "aaaaaaaa"], ["cab", "aaaaaaaa"]):
            # /* Example
            #  *  Input: str1 = "abac", str2 = "cab"
            #  *  Output: "cabac"
            #  *
            #  *  Input: str1 = "aaaaaaaa", str2 = "aaaaaaaa"
            #  *  Output: "aaaaaaaa"
            #  */
            logging.info("Input: str1 = \"%s\", str2 = \"%s\"", str1, str2)

            retVal = pSolution.shortestCommonSupersequence(str1, str2)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
