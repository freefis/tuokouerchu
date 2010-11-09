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
import os
path = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.append(path)

try:
    from base import common
except:
    print("No such path")


classify_cursor = common.get_cursor("classify")
groupbuy_cursor = common.get_cursor("groupbuy")
#print dir(groupbuy_cursor); sys.exit(0);




for one in groupbuy_cursor.find():
    print one['title']
    data = {}
    data['groupbuy_id'] = one['_id']
    data['category'] = {} 
    try:
        data['category']['food'] += 1
    except KeyError:
        data['category']['food'] = 1
    classify_cursor.insert(data)

#classify_cursor.remove()
for one in classify_cursor.find():
    groupbuy_id = one['groupbuy_id']
    groupbuy = groupbuy_cursor.find_one({"_id":groupbuy_id})
    print groupbuy['title'] + "[" + groupbuy_id.__str__() + "]"

