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
    def get_words(self, words: List[str], maxWidth: int, i: int) -> List[str]:
        retVal = []

        curr_length = 0
        while (i < len(words)) and (curr_length + len(words[i]) <= maxWidth):
            retVal.append(words[i])
            curr_length += len(words[i]) + 1
            i += 1

        return retVal

    def create_line(self, words: List[str], maxWidth: int, line: List[str], i: int) -> str:
        retVal = ""

        base_length = -1
        for word in line:
            base_length += len(word) + 1
        extra_spaces = maxWidth - base_length
        if (len(line) == 1) or (i == len(words)):
            retVal = " ".join(line) + " " * extra_spaces
            return retVal

        word_count = len(line) - 1
        spaces_per_word = extra_spaces // word_count
        needs_extra_space = extra_spaces % word_count
        for j in range(needs_extra_space):
            line[j] += " "
        for j in range(word_count):
            line[j] += " " * spaces_per_word
        retVal = " ".join(line)

        return retVal

    def fullJustify(self, words: List[str], maxWidth: int) -> List[str]:
        retVal = []

        i = 0
        while i < len(words):
            current_line = self.get_words(words, maxWidth, i)
            i += len(current_line)
            retVal.append(self.create_line(words, maxWidth, current_line, i))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for words, maxWidth in zip([
                ["This", "is", "an", "example", "of", "text", "justification."],
                ["What", "must", "be", "acknowledgment", "shall", "be"],
                ["Science", "is", "what", "we", "understand", "well", "enough", "to", "explain", "to", "a", "computer.",
                 "Art", "is", "everything", "else", "we", "do"]],
                [16, 16, 20]):
            # /* Example
            #  *  Input: words = ["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16
            #  *  Output:
            #  *  [
            #  *     "This    is    an",
            #  *     "example  of text",
            #  *     "justification.  "
            #  *  ]
            #  *
            #  *  Input: words = ["What","must","be","acknowledgment","shall","be"], maxWidth = 16
            #  *  Output:
            #  *  [
            #  *    "What   must   be",
            #  *    "acknowledgment  ",
            #  *    "shall be        "
            #  *  ]
            #  *
            #  *  Input: words = ["Science","is","what","we","understand","well","enough","to","explain","to","a","computer.",
            #  *  "Art","is","everything","else","we","do"], maxWidth = 20
            #  *  Output:
            #  *  [
            #  *    "Science  is  what we",
            #  *    "understand      well",
            #  *    "enough to explain to",
            #  *    "a  computer.  Art is",
            #  *    "everything  else  we",
            #  *    "do                  "
            #  *  ]
            #  */
            logging.info("Input: words = %s, maxWidth = %s", words, maxWidth)

            retVal = pSolution.fullJustify(words, maxWidth)
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
