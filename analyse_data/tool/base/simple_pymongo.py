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
from pymongo.objectid import ObjectId
import config

class Extend_Connection(Connection):
    pass

class Extend_Collection(pymongo.collection.Collection):
    def auto_incr_id(self,object_id):
        if type(object_id) == "str":
            object_id = ObjectId(objectid)

        self.db.command(
                "findandmodify",
                col,
                query={'_id': object_id}, 
                update={'$inc': {'id': 1}}, 
                upset=True, 
                new=True
        )


class Simple_pymongo(Extend_Connection):
    @staticmethod
    def get_instance():
        obj = Simple_pymongo(config.mongo['hosts'])
        return obj


    def __init__(self,*args,**kargs):
        self.conn_obj = Connection(*args,**kargs)


    def create_cursor(self,dbname=config.mongo['dbname']):
        self.db = self.conn_obj.__getattr__(dbname)
        return self.db


    def auto_incr_id(self,col,object_id):
        if type(object_id) == "str":
            object_id = ObjectId(objectid)

        self.db.command(
                "findandmodify",
                col,
                query={'_id': object_id}, 
                update={'$inc': {'id': 1}}, 
                upset=True, 
                new=True
        )

    def _set_db(self,dbname):
        self.db = self.conn_obj.__getattr__(dbname)

    def _set_collection(self,collection):
        self.col = self.db.__getattr__(collection)
