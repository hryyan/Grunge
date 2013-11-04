class ClassName(object):
    """docstring for ClassName"""

    a = False
    def __init__(self):
        super(ClassName, self).__init__()
        self.a = self.__class__.a

ClassName.a = 0
c = ClassName()
print c.a