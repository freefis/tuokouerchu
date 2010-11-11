#!/usr/bin/env python
# -*- coding:utf-8 -*-

#-------------------------------------------
# Auther      : free.Wang<freefis@gmail.com> 
# Licence     : License on GPL Licence
# Description :
#    ...
# Archieved   : Mar 2nd 2009  
#-------------------------------------------

from simple_pymongo import Simple_pymongo 
import pymongo
import config

conn = Simple_pymongo(",".join(config.mongo['hosts']))

def get_db(dbname):
    return conn.__getattr__(dbname)

def get_cursor(tbname,dbname=config.mongo['dbname']):
    db = conn.__getattr__(dbname)
    cursor = db.__getattr__(tbname)
    return cursor

if __name__ == '__main__':
    d =   get_cursor("groupbuy")
    print d._Collection__name
