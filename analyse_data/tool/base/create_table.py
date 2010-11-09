#!/usr/bin/env python
# -*- coding:utf-8 -*-

#-------------------------------------------
# Auther      : free.Wang<freefis@gmail.com> 
# Licence     : License on GPL Licence
# Description :
#    ...
# Archieved   : Mar 2nd 2009  
#-------------------------------------------

from common import get_cursor
import pymongo


c = get_cursor("classify")
c.ensure_index([('groupbuy_id',pymongo.ASCENDING)],unique=True)

c = get_cursor("groupbuy")
c.ensure_index([('title',pymongo.ASCENDING)],unique=True)

