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
    def generateSequences(self, tiles: str, current: str, used: list, sequences: set) -> None:
        sequences.add(current)

        # Try adding each unused character to current sequence
        for pos, char in enumerate(tiles):
            if used[pos] == True:
                continue
            used[pos] = True
            self.generateSequences(tiles, current + char, used, sequences)
            used[pos] = False

    def numTilePossibilities(self, tiles: str) -> int:
        retVal = 0

        tilesSize = len(tiles)

        sequences = set()
        used = [False] * tilesSize
        self.generateSequences(tiles, "", used, sequences)  # Generate all possible sequences including empty string
        retVal = len(sequences) - 1  # Subtract 1 to exclude empty string from count

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for tiles in ["AAB", "AAABBC", "V"]:
            # /* Example
            #  *  Input: tiles = "AAB"
            #  *  Output: 8
            #  *
            #  *  Input: tiles = "AAABBC"
            #  *  Output: 188
            #  *
            #  *  Input: tiles = "V"
            #  *  Output: 1
            #  */
            logging.info("Input: tiles = \"%s\"", tiles)

            retVal = pSolution.numTilePossibilities(tiles)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
