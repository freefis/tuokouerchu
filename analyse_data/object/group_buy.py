#!/usr/bin/env python
# -*- coding:utf-8 -*-

#-------------------------------------------
# Auther      : free.Wang<freefis@gmail.com> 
# Licence     : License on GPL Licence
# Description :
#    ...
# Archieved   : Mar 2nd 2009  
#-------------------------------------------

import os
import sys

DIR_PATH = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TOOL_PATH = os.path.join(DIR_PATH,"tool")

sys.path.append(TOOL_PATH)

try:
    from pymmseg import mmseg
except:
    print TOOL_PATH
    print("pymmseg not exist")

try:
    import pymongo
except:
    print("You need install pymongo")

import simple_mmseg 


conn = pymongo.Connection("127.0.0.1",10001)
db = conn.tuokouerchu
cursor = db.groupbuy
import time
a = time.time()
for i in cursor.find():
    title = i['title'].encode("utf8")
    words = simple_mmseg.parse_words(title)
    s = title+":"+" ".join(words)
#    os.system("echo \"%s\" >> content" % s)
    simple_mmseg.cache_words(words)
    for i in words:
        if i.__len__() <= 3:
#b = time.time()
#print (b-a) / cursor.find().count()
           os.system("echo %s >> singple" % i)
#    break
simple_mmseg.update_words()







