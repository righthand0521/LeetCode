import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop
from copy import deepcopy


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
    def smallestSufficientTeam(self, req_skills: List[str], people: List[List[str]]) -> List[int]:
        retVal = []

        req_skillsSize = len(req_skills)
        peopleSize = len(people)

        req_skills_index = {skill: index for index,
                            skill in enumerate(req_skills)}

        dp = [peopleSize] * (1 << req_skillsSize)
        dp[0] = 0

        prev_skill = [0] * (1 << req_skillsSize)
        prev_people = [0] * (1 << req_skillsSize)
        for index, value in enumerate(people):
            cur_skill = 0

            for skill in value:
                cur_skill |= (1 << req_skills_index[skill])

            for prev in range(1 << req_skillsSize):
                comb = prev | cur_skill
                if dp[comb] > dp[prev] + 1:
                    dp[comb] = dp[prev] + 1
                    prev_skill[comb] = prev
                    prev_people[comb] = index

        index = (1 << req_skillsSize) - 1
        while index > 0:
            retVal.append(prev_people[index])
            index = prev_skill[index]
        retVal.sort()

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for req_skills, people in zip(
            [["java", "nodejs", "reactjs"], ["algorithms",
                                             "math", "java", "reactjs", "csharp", "aws"]],
            [[["java"], ["nodejs"], ["nodejs", "reactjs"]],
             [["algorithms", "math", "java"], ["algorithms", "math", "reactjs"], ["java", "csharp", "aws"],
              ["reactjs", "csharp"], ["csharp", "math"], ["aws", "java"]]]):
            # /* Example
            #  *  Input: req_skills = ["java","nodejs","reactjs"], people = [["java"],["nodejs"],["nodejs","reactjs"]]
            #  *  Output: [0,2]
            #  *
            #  *  Input: req_skills = ["algorithms","math","java","reactjs","csharp","aws"],
            #  *  people = [["algorithms","math","java"],["algorithms","math","reactjs"],["java","csharp","aws"],
            #  *  ["reactjs","csharp"],["csharp","math"],["aws","java"]]
            #  *  Output: [1,2]
            #  */
            logging.info("Input: req_skills = %s, people = %s",
                         req_skills, people)

            retVal = pSolution.smallestSufficientTeam(req_skills, people)
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
