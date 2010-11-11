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
from pymongo import Connection

class Simple_pymongo(Connection):
    def __init__(self,*args,**kargs):
        self.conn_obj = Connection.__init__(self,*args,**kargs)

    def set_db(self,dbname):
        self.db = self.conn_obj.__getattr__(dbname)

    def set_collection(self,collection):
        self.col = self.db.__getattr__(collection)

    def create_cursor(self,dbname,collection):
        self.set_db(dbname)
        self.set_col(collection)
        return cursor

    def auto_incr_id(self,row):
        self.db.command(
                "findandmodify",
                self.col._Collection__name,
                query={'_id': Row['_id']}, 
                update={'$inc': {'id': 1}}, 
                upset=True, 
                new=True
        )




