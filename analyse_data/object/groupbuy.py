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
    from wordseg import Simple_wordseg as Simple_mmseg
except:
    print TOOL_PATH
    print("pymmseg not exist")

try:
    import pymongo
except:
    print("You need install pymongo")

import time


conn = pymongo.Connection("127.0.0.1",10001)
db = conn.tuokouerchu
cursor = db.groupbuy
a = time.time()
obj = Simple_mmseg()
obj.set_library_path()
for i in cursor.find():
    title = i['title'].encode("utf8")
    print "-"*10
    print title
    words = obj.parse_words(title)
    print i['_id']
    continue
    for i in words:
        if i.__len__() <= 3:
           continue
           os.system("echo %s >> singple" % i)
        else:
           print i

b = time.time()
print (b-a) / cursor.find().count()







