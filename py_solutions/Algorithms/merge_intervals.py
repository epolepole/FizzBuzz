# Definition for an interval.
class Interval:
    def __init__(self, s=0, e=0):
        self.start = s
        self.end = e

    def __str__(self):
        return "(" + str(self.start) + "," + str(self.end) + ")"


def printInterList(intervals):
    for p in intervals:
        print(str(p))

# given [1,3],[2,6],[8,10],[15,18]
# return [1,6],[8,10],[15,18]


class Solution:
    def merge(self, intervals):
        """
        :type intervals: List[Interval]
        :rtype: List[Interval]
        """
        'Brute force: probably we need to sort them before and then iterate them in an intelligent way taking into account the way we sorted'
        'We could sort ascending by first, descending by second'

        solution_intervals = list()
        # printInterList(intervals)
        intervals = sorted(intervals, key=lambda inter: inter.start)
        # printInterList(intervals)
        temp_min = intervals[0].start
        temp_max = intervals[0].end
        for interval in intervals:
            if interval.start > temp_max:
                solution_intervals.append(Interval(temp_min, temp_max))
                temp_min = interval.start
                temp_max = interval.end
                continue
            if interval.end > temp_max:
                temp_max = interval.end
        solution_intervals.append(Interval(temp_min, temp_max))

        printInterList(solution_intervals)
        return solution_intervals


sol = Solution()

inte = list()
inte.append(Interval(0, 5))
inte.append(Interval(2, 3))
inte.append(Interval(7, 9))
inte.append(Interval(10, 12))
inte.append(Interval(9, 11))
inte.append(Interval(2, 6))
# printInterList(inte)
sol.merge(inte)
