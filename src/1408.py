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
    def computeLPSArray(self, substring: str) -> List[int]:
        retVal = []

        substringSize = len(substring)
        retVal = [0] * substringSize

        length = 0
        currentIndex = 1
        while currentIndex < substringSize:
            if substring[currentIndex] == substring[length]:
                length += 1
                retVal[currentIndex] = length
                currentIndex += 1
                continue

            if length > 0:  # Backtrack using Longest Prefix Suffix Array to find a shorter match.
                length = retVal[length - 1]
            else:
                currentIndex += 1

        return retVal

    def isSubstringOf(self, substring: str, main: str, lps) -> bool:
        retVal = False

        mainSize = len(main)
        substringSize = len(substring)
        mainIndex = 0
        substringIndex = 0
        while mainIndex < mainSize:
            if main[mainIndex] == substring[substringIndex]:
                mainIndex += 1
                substringIndex += 1
                if substringIndex == substringSize:
                    retVal = True
                    return retVal
                continue

            if substringIndex > 0:
                # Use the Longest Prefix Suffix to skip unnecessary comparisons.
                substringIndex = lps[substringIndex - 1]
            else:
                mainIndex += 1

        return retVal

    def stringMatching(self, words: List[str]) -> List[str]:
        retVal = []

        wordsSize = len(words)
        for currentWordIndex in range(wordsSize):
            lps = self.computeLPSArray(words[currentWordIndex])

            # Compare the current word with all other words.
            for otherWordIndex in range(wordsSize):
                if currentWordIndex == otherWordIndex:
                    continue  # Skip comparing the word with itself.

                # Check if the current word is a substring of another word.
                if self.isSubstringOf(words[currentWordIndex], words[otherWordIndex], lps) == True:
                    retVal.append(words[currentWordIndex])
                    break  # No need to check further for this word.

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for words in [["mass", "as", "hero", "superhero"], ["leetcode", "et", "code"], ["blue", "green", "bu"]]:
            # /* Example
            #  *  Input: words = ["mass","as","hero","superhero"]
            #  *  Output: ["as","hero"]
            #  *
            #  *  Input: words = ["leetcode","et","code"]
            #  *  Output: ["et","code"]
            #  *
            #  *  Input: words = ["blue","green","bu"]
            #  *  Output: []
            #  */
            logging.info("Input: words = %s", words)

            retVal = pSolution.stringMatching(words)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
