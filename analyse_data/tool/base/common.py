#!/usr/bin/env python
# -*- coding:utf-8 -*-

#-------------------------------------------
# Auther      : free.Wang<freefis@gmail.com> 
# Licence     : License on GPL Licence
# Description :
#    ...
# Archieved   : Mar 2nd 2009  
#-------------------------------------------

import pymongo
import config

conn = pymongo.Connection(",".join(config.mongo['hosts']))

def get_cursor(tbname,dbname=config.mongo['dbname']):
    db = conn.__getattr__(dbname)
    cursor = db.__getattr__(tbname)
    return cursor

if __name__ == '__main__':
    for i in  get_cursor("groupbuy").find():
        print i
