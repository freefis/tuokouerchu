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
try:
    from pymmseg import  mmseg
except:
    pass


class Simple_mmseg(object):
    def __init__(self,text):
        self.library_path = mmseg.get_default_library_path()
        self.cache_path = mmseg.get_default_cache_path()

        mmseg.dict_load_defaults()
        self.aobj = mmseg.Algorithm(text)
        self.parsed_words = []
        for tok in self.aobj:
            self.parsed_words.append(tok.text)

    def get_result(self,text):
        """ comment """
        return self.parsed_words

    def cache_words(self):
        self.cobj = mmseg.Cache_words()
        self.cobj.auto_run(self.parsed_words)

    def update_words(self):
        self.uobj = mmseg.Update_words(self.library_path)

        self.uobj.set_cache_path(self.cache_path)
        self.uobj.auto_run()

        self.cobj.clean()

        return self.uobj


if __name__ == '__main__':
    s = Simple_mmseg("fdsfsdf")
    s.cache_words()
