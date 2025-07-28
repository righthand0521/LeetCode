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
    def buddyStrings(self, s: str, goal: str) -> bool:
        retVal = False

        sSize = len(s)
        goalSize = len(goal)
        if sSize != goalSize:
            return retVal

        if s == goal:
            # If we have 2 same characters in string 's', we can swap them and still the strings will remain equal.
            frequency = [0] * 26
            for ch in s:
                frequency[ord(ch) - ord('a')] += 1
                if frequency[ord(ch) - ord('a')] == 2:
                    retVal = True
                    return retVal

            # Otherwise, if we swap any two characters, it will make the strings unequal.
            return retVal

        firstIndex = -1
        secondIndex = -1
        for i in range(sSize):
            if s[i] != goal[i]:
                if firstIndex == -1:
                    firstIndex = i
                elif secondIndex == -1:
                    secondIndex = i
                else:
                    # We have at least 3 indices with different characters,
                    # thus, we can never make the strings equal with only one swap.
                    return retVal

        if secondIndex == -1:
            # We can't swap if the character at only one index is different.
            return retVal

        # All characters of both strings are the same except two indices.
        retVal = (s[firstIndex] == goal[secondIndex]) and (
            s[secondIndex] == goal[firstIndex])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, goal in zip(["ab", "ab", "aa", "ab", "abcaa", "abcd"], ["ba", "ab", "aa", "babbb", "abcbb", "abcd"]):
            # /* Example
            #  *  Input: s = "ab", goal = "ba"
            #  *  Output: true
            #  *
            #  *  Input: s = "ab", goal = "ab"
            #  *  Output: false
            #  *
            #  *  Input: s = "aa", goal = "aa"
            #  *  Output: true
            #  *
            #  *  Input: s = "ab", goal = "babbb"
            #  *  Output: false
            #  *
            #  *  Input: s = "abcaa", goal = "abcbb
            #  *  Output: false
            #  *
            #  *  Input: s = "abcd", goal = "abcd"
            #  *  Output: false
            #  */
            logging.info("Input: s = \"%s\", goal = \"%s\"", s, goal)

            retVal = pSolution.buddyStrings(s, goal)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
