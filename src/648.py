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
    def shortest_root(self, word: str, dict_set: set) -> str:
        retVal = word   # There is not a corresponding root in the dictionary

        wordSize = len(word)
        for i in range(wordSize):  # Find the shortest root of the word in the dictionary
            root = word[0:i]
            if root in dict_set:
                retVal = root
                break

        return retVal

    def replaceWords(self, dictionary: List[str], sentence: str) -> str:
        retVal = None

        dict_set = set(dictionary)

        wordArray = sentence.split()
        wordArraySize = len(wordArray)

        # Replace each word in sentence with the corresponding shortest root
        for word in range(wordArraySize):
            wordArray[word] = self.shortest_root(wordArray[word], dict_set)
        retVal = " ".join(wordArray)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for dictionary, sentence in zip([["cat", "bat", "rat"], ["a", "b", "c"]],
                                        ["the cattle was rattled by the battery", "aadsfasf absbs bbab cadsfafs"]):
            # /* Example
            #  *  Input: dictionary = ["cat","bat","rat"], sentence = "the cattle was rattled by the battery"
            #  *  Output: "the cat was rat by the bat"
            #  *
            #  *  Input: dictionary = ["a","b","c"], sentence = "aadsfasf absbs bbab cadsfafs"
            #  *  Output: "a a b c"
            #  */
            logging.info("Input: dictionary = %s, sentence = \"%s\"",
                         dictionary, sentence)

            retVal = pSolution.replaceWords(dictionary, sentence)
            logging.info("Output: \"%s\"", retVal)

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
