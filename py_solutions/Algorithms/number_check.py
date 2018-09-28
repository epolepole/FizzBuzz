import re


class Solution:
    def isNumber(self, s):
        """
        :type s: str
        :rtype: bool
        """
        'We need to find the different types of numbers'
        'integers, decimals, exponential'
        '653, 32.45, 3e10, 3.4e10, -134'
        if re.search('^[-+]?(\d+\.?\d*|\d*\.?\d+)(e\d+)?$', s):
            return True
        return False


sol = Solution()

print(str(sol.isNumber('-05'))      + ' ' + str(True))
print(str(sol.isNumber('05.'))      + ' ' + str(True))
print(str(sol.isNumber('.56'))      + ' ' + str(True))
print(str(sol.isNumber('05.56'))    + ' ' + str(True))
print(str(sol.isNumber('05e5'))     + ' ' + str(True))
print(str(sol.isNumber('05e56'))    + ' ' + str(True))
print(str(sol.isNumber('-05.5e6'))  + ' ' + str(True))
print(str(sol.isNumber('-05.5e69')) + ' ' + str(True))
print(str(sol.isNumber('-05.56'))   + ' ' + str(True))
print(str(sol.isNumber('-05.e10'))  + ' ' + str(True))
print(str(sol.isNumber('-05.56e'))  + ' ' + str(False))
print(str(sol.isNumber('e3 '))  + ' ' + str(False))


print(str(sol.isNumber('-05..56'))  + ' ' + str(False))
print(str(sol.isNumber('--05'))     + ' ' + str(False))



print(str(sol.isNumber('05ee56'))   + ' ' + str(False))
print(str(sol.isNumber('05e56e4'))  + ' ' + str(False))
print(str(sol.isNumber('05e56e'))   + ' ' + str(False))
print(str(sol.isNumber('.'))      + ' ' + str(False))
print(str(sol.isNumber(' '))      + ' ' + str(False))
print(str(sol.isNumber('a'))      + ' ' + str(False))
