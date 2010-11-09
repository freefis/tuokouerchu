#!/usr/bin/env python
# -*- coding:utf-8 -*-

#-------------------------------------------
# Auther      : free.Wang<freefis@gmail.com> 
# Licence     : License on GPL Licence
# Description :
#    ...
# Archieved   : Mar 2nd 2009  
#-------------------------------------------

import sys
filename = sys.argv[1]

if __name__ == "__main__":
    if filename.endswith(".txt"):
        dicname = filename.replace(".txt",".dic")
    else:
        dicname = filename + ".dic"

    rows = open(filename).readlines()

    i = 0;
    content = ""
    for one in rows:
        content += "0 %s" % (one)


    f = open(dicname,"wb")
    f.write(content)
    f.close()



