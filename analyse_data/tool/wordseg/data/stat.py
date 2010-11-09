#!/usr/bin/env python
# -*- coding:utf-8 -*-

#-------------------------------------------
# Auther      : free.Wang<freefis@gmail.com> 
# Licence     : License on GPL Licence
# Description :
#    ...
# Archieved   : Mar 2nd 2009  
#-------------------------------------------


count = 0
result = []
for i in open("library.dic").readlines():
    if i.__len__() >= 6*3:
        count += 1
    else:
        result.append(i)


print count
content = "".join(result)
content += "\n"
f = open("test.dic","wb")
f.write(content)
f.close()

