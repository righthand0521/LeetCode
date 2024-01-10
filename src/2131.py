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
    def __init__(self):
        self.method = 2

        if self.method == 1:
            print("A Hash Map Approach")
        elif self.method == 2:
            print("A Two-Dimensional Array Approach")
        print()

    def longestPalindrome(self, words: List[str]) -> int:
        retVal = 0

        central = False
        if self.method == 1:
            # a count variable contains the number of occurrences of each word
            count = Counter(words)

            for word, count_of_the_word in count.items():
                # if the word is a palindrome
                if word[0] == word[1]:
                    if count_of_the_word % 2 == 0:
                        retVal += count_of_the_word
                    else:
                        retVal += count_of_the_word - 1
                        central = True
                # consider a pair of non-palindrome words,
                # such that one is the reverse of another word[1] + word[0] is the reversed word
                elif word[0] < word[1]:
                    retVal += 2 * min(count_of_the_word,
                                      count[word[1] + word[0]])
        elif self.method == 2:
            alphabet_size = 26
            count = [[0 for j in range(alphabet_size)]
                     for i in range(alphabet_size)]

            for word in words:
                count[ord(word[0]) - ord('a')][ord(word[1]) - ord('a')] += 1

            for i in range(alphabet_size):
                if count[i][i] % 2 == 0:
                    retVal += count[i][i]
                else:
                    retVal += count[i][i] - 1
                    central = True
                for j in range(i + 1, alphabet_size):
                    retVal += 2 * min(count[i][j], count[j][i])

        if central:
            retVal += 1
        retVal = 2 * retVal

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for words in [["lc", "cl", "gg"], ["ab", "ty", "yt", "lc", "cl", "ab"], ["cc", "ll", "xx"]]:
            # /* Example
            #  *  Input: words = ["lc","cl","gg"]
            #  *  Output: 6
            #  *
            #  *  Input: words = ["ab","ty","yt","lc","cl","ab"]
            #  *  Output: 8
            #  *
            #  *  Input: words = ["cc","ll","xx"]
            #  *  Output: 2
            #  */
            logging.info("Input: words = %s", words)

            retVal = pSolution.longestPalindrome(words)
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
