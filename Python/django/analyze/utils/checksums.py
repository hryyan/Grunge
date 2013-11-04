###############################################################
#
#   added by YZ: 2013/09/13
#   Specification: LUHN算法，主要用来计算信用卡等证件号码的合法性。
#   1、从卡号最后一位数字开始,偶数位乘以2,如果乘以2的结果是两位数，将两个位上数字相加保存。
#   2、把所有数字相加,得到总和。
#   3、如果信用卡号码是合法的，总和可以被10整除。

#
###############################################################

"""
Common checksum routines (used in multiple localflavor/ cases, for example).
"""

__all__ = ['luhn',]

LUHN_ODD_LOOKUP = (0, 2, 4, 6, 8, 1, 3, 5, 7, 9) # sum_of_digits(index * 2)

def luhn(candidate):
    """
    Checks a candidate number for validity according to the Luhn
    algorithm (used in validation of, for example, credit cards).
    Both numeric and string candidates are accepted.
    """
    if not isinstance(candidate, basestring):
        candidate = str(candidate)
    try:
        evens = sum([int(c) for c in candidate[-1::-2]])
        odds = sum([LUHN_ODD_LOOKUP[int(c)] for c in candidate[-2::-2]])
        return ((evens + odds) % 10 == 0)
    except ValueError:  # Raised if an int conversion fails
        return False
