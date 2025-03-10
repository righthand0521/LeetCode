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
    def isVowel(self, c: str) -> bool:
        retVal = (c == "a") or (c == "e") or (c == "i") or (c == "o") or (c == "u")

        return retVal

    def countOfSubstrings(self, word: str, k: int) -> int:
        retVal = 0

        wordSize = len(word)

        nextConsonant = [0] * wordSize  # Array to compute index of next consonant for all indices
        nextConsonantIndex = wordSize
        for i in range(wordSize - 1, -1, -1):
            nextConsonant[i] = nextConsonantIndex
            if self.isVowel(word[i]) == False:
                nextConsonantIndex = i

        vowelCount = {}  # Dictionary to keep counts of vowels
        consonantCount = 0  # Count of consonants
        start = 0
        end = 0
        while end < wordSize:
            newLetter = word[end]
            if self.isVowel(newLetter) == True:
                vowelCount[newLetter] = vowelCount.get(newLetter, 0) + 1
            else:
                consonantCount += 1

            # Shrink window if too many consonants are present
            while (consonantCount > k):
                startLetter = word[start]
                if self.isVowel(startLetter) == True:
                    vowelCount[startLetter] -= 1
                    if vowelCount[startLetter] == 0:
                        del vowelCount[startLetter]
                else:
                    consonantCount -= 1
                start += 1

            # Try to shrink if window is valid
            while (start < wordSize) and (len(vowelCount) == 5) and (consonantCount == k):
                retVal += nextConsonant[end] - end
                startLetter = word[start]
                if self.isVowel(startLetter) == True:
                    vowelCount[startLetter] -= 1
                    if vowelCount[startLetter] == 0:
                        del vowelCount[startLetter]
                else:
                    consonantCount -= 1
                start += 1

            end += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for word, k in zip(["aeioqq", "aeiou", "ieaouqqieaouqq"], [1, 0, 1]):
            # /* Example
            #  *  Input: word = "aeioqq", k = 1
            #  *  Output: 0
            #  *
            #  *  Input: word = "aeiou", k = 0
            #  *  Output: 1
            #  *
            #  *  Input: word = "ieaouqqieaouqq", k = 1
            #  *  Output: 3
            #  */
            logging.info("Input: word = \"%s\", k = %s", word, k)

            retVal = pSolution.countOfSubstrings(word, k)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
