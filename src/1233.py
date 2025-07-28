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
    def removeSubfolders(self, folder: List[str]) -> List[str]:
        retVal = []

        # Sort the folders alphabetically
        folder.sort()

        # Initialize the retVal list and add the first folder
        retVal = [folder[0]]

        # Iterate through each folder and check if it's a sub-folder of the last added folder in the retVal
        folderSize = len(folder)
        for i in range(1, folderSize):
            lastFolder = retVal[-1]
            lastFolder += "/"

            # Check if the current folder starts with the last added folder path
            if not folder[i].startswith(lastFolder):
                retVal.append(folder[i])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for folder in [
            ["/a", "/a/b", "/c/d", "/c/d/e", "/c/f"],
            ["/a", "/a/b/c", "/a/b/d"],
            ["/a/b/c", "/a/b/ca", "/a/b/d"]
        ]:
            # /* Example
            #  *  Input: folder = ["/a","/a/b","/c/d","/c/d/e","/c/f"]
            #  *  Output: ["/a","/c/d","/c/f"]
            #  *
            #  *  Input: folder = ["/a","/a/b/c","/a/b/d"]
            #  *  Output: ["/a"]
            #  *
            #  *  Input: folder = ["/a/b/c","/a/b/ca","/a/b/d"]
            #  *  Output: ["/a/b/c","/a/b/ca","/a/b/d"]
            #  */
            logging.info("Input: folder = %s", folder)

            retVal = pSolution.removeSubfolders(folder)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
