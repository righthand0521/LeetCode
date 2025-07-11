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
    def mostBooked(self, n: int, meetings: List[List[int]]) -> int:
        retVal = 0

        meetings = sorted(meetings)

        room_availability_time = [0] * n
        meeting_count = [0] * n
        for start, end in meetings:
            min_room_availability_time = float('inf')
            min_available_time_room = 0
            found_unused_room = False

            for i in range(n):
                if room_availability_time[i] <= start:
                    found_unused_room = True
                    meeting_count[i] += 1
                    room_availability_time[i] = end
                    break

                if min_room_availability_time > room_availability_time[i]:
                    min_room_availability_time = room_availability_time[i]
                    min_available_time_room = i

            if found_unused_room is False:
                room_availability_time[min_available_time_room] += end - start
                meeting_count[min_available_time_room] += 1

        retVal = meeting_count.index(max(meeting_count))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, meetings in zip([2, 3], [[[0, 10], [1, 5], [2, 7], [3, 4]], [[1, 20], [2, 10], [3, 5], [4, 9], [6, 8]]]):
            # /* Example
            #  *  Input: n = 2, meetings = [[0,10],[1,5],[2,7],[3,4]]
            #  *  Output: 0
            #  *
            #  *  Input: n = 3, meetings = [[1,20],[2,10],[3,5],[4,9],[6,8]]
            #  *  Output: 1
            #  */
            logging.info("Input: n = %s, meetings = %s", n, meetings)

            retVal = pSolution.mostBooked(n, meetings)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
