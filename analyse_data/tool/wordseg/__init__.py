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
    import wordseg as mmseg
except:
    pass


class Simple_wordseg(object):
    def __init__(self):
        self.cache_path = None
        self.library_path = None

    def set_cache_path(self,path=None):
        if path is None:
            self.cache_path = mmseg.get_default_cache_path()
        else:
            self.cache_path = path

    def set_library_path(self,path=None):
        if path is None:
            self.library_path = mmseg.get_default_library_path()
        else:
            self.library_path = path
        mmseg.dict_load_words(self.library_path)


    def parse_words(self,text):
        if self.library_path is None:
            print("please run set_library_path()")
            sys.exit(0)

        self.aobj = mmseg.Algorithm(text)
        self.parsed_words = []
        for tok in self.aobj:
            self.parsed_words.append(tok.text)
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
    text = """
。 ...
zhidao.baidu.com › 教育/科学 › 科学技术 › 工程技术科学 - 网页快照
FMS是什么--IT术语-Java入门培训网
FMS是一个完全基于软件环境的多媒体实时通讯环境，代表了当前实时通讯领域内的发展的方向，并且，其自身也融合了大量的新特色，用于创建下一代通讯应用程序
...
    """
    s = Simple_mmseg(text)
    for i in  s.parsed_words:
        print i
    s.cache_words()
