#!/usr/bin/env python
# -*- coding:utf-8 -*-

#-------------------------------------------
# Auther      : free.Wang<freefis@gmail.com> 
# Licence     : License on GPL Licence
# Description :
#    ...
# Archieved   : Mar 2nd 2009  
#-------------------------------------------

from common import get_cursor,conn,get_db
import pymongo

d = get_db("tuokouerchu")

c = get_cursor("classify")
c.ensure_index([('groupbuy_id',pymongo.ASCENDING)],unique=True)

c = get_cursor("groupbuy")
c.ensure_index([('title',pymongo.ASCENDING)],unique=True)

c = get_cursor("emotion")
c.ensure_index([('name',pymongo.ASCENDING)],unique=True)

#d.drop_collection("emotion")

#for i in ["高兴","郁闷","伤心","沮丧","饿","宅","无聊"]: 
#    c.insert({"name":i})

for i in c.find():



#    c.find_and_modify(    
#        {"name": i['name'] },{"$inc": {"id":1 }},True
#   );

for i in c.find():
    print i
