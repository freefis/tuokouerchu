#!/usr/bin/env python
# -*- coding:utf-8 -*-

import sys
#-------------------------------------------
# Auther      : free.Wang<freefis@gmail.com> 
# Licence     : License on GPL Licence
# Description :
#    ...
# Archieved   : Mar 2nd 2009  
#-------------------------------------------
from simple_pymongo import Simple_pymongo
import pymongo

get_instance = Simple_pymongo.get_instance


obj = get_instance()
c = obj.create_cursor("tuokouerchu")
c.classify.ensure_index([('groupbuy_id',pymongo.ASCENDING)],unique=True)


c.groupbuy.ensure_index([('title',pymongo.ASCENDING)],unique=True)

c.emotion.ensure_index([('name',pymongo.ASCENDING)],unique=True)

#c.drop_collection("emotion")

from pymongo.objectid import ObjectId
import datetime


obj = get_instance()
c = obj.create_cursor("tuokouerchu")
c.drop_collection("emotion")

import random
k = 0
for i in ["高兴","郁闷","伤心","沮丧","饿","宅","无聊"]: 
    obj = get_instance()
    c = obj.create_cursor("tuokouerchu")
    row = c.emotion.insert({"id":k,"name":random.choice(range(1,100))})
    k+=1


timebinray = ObjectId.from_datetime(  datetime.datetime.now()  )
for row in c.emotion.find():
    obj = get_instance()
    obj.create_cursor("tuokouerchu")
    print row
    obj.auto_incr_id("emotion",row['_id'])
    del obj



for row in c.emotion.find():
    print row
