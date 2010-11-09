# -*- coding: utf-8 -*-

import sys
import os
from ctypes import *
from os.path import join, dirname, abspath, exists

if sys.platform == 'win32':
    ext = 'dll'
else:
    ext = 'so'
    
mmseg = cdll.LoadLibrary(join(dirname(__file__),
                              'cpp',
                              'libcal.%s' % ext))

DIRNAME = os.path.dirname(os.path.abspath(__file__))
CACHE_PATH = os.path.join(DIRNAME,"data","cache")
LIBRARY_PATH = os.path.join(DIRNAME,"data","library.dic")

########################################
# Init function prototypes
########################################
mmseg.mmseg_load_chars.argtypes = [c_char_p]
mmseg.mmseg_load_chars.restype  = c_int

mmseg.mmseg_load_words.argtypes = [c_char_p]
mmseg.mmseg_load_words.restype  = c_int

mmseg.mmseg_dic_add.argtypes = [c_char_p, c_int, c_int]
mmseg.mmseg_dic_add.restype  = None

mmseg.mmseg_algor_create.argtypes = [c_char_p, c_int]
mmseg.mmseg_algor_create.restype  = c_void_p

mmseg.mmseg_algor_destroy.argtypes = [c_void_p]
mmseg.mmseg_algor_destroy.restype  = None

mmseg.mmseg_next_token.argtypes = [c_void_p]
mmseg.mmseg_next_token.restype  = Token

# update words
mmseg.update_words_init.argtypes = [c_char_p]
mmseg.update_words_init.restype  = c_void_p

mmseg.update_words_incr_words_count_from_cache.argtypes = [c_void_p,c_char_p]
mmseg.update_words_incr_words_count_from_cache.restype  = None

mmseg.update_words_write_file.argtypes = [c_void_p]
mmseg.update_words_write_file.restype  = c_int

mmseg.update_words_destroy.argtypes = [c_void_p]
mmseg.update_words_destroy.restype  = None

# cache words
mmseg.cache_words_init.argtypes = [c_char_p]
mmseg.cache_words_init.restype  = c_void_p

mmseg.cache_words_add_word.argtypes = [c_void_p,c_char_p]
mmseg.cache_words_add_word.restype  = None

mmseg.cache_words_write_file.argtypes = [c_void_p]
mmseg.cache_words_write_file.restype  = c_int

mmseg.cache_words_clean.argtypes = [c_void_p]
mmseg.cache_words_clean.restype  = int

mmseg.cache_words_destroy.argtypes = [c_void_p]
mmseg.cache_words_destroy.restype  = None

mmseg.cache_words_get_cache_words.argtypes = [c_void_p]
mmseg.cache_words_get_cache_words.restype  = c_char_p

mmseg.cache_words_get_iter_cache_word.argtypes = [c_void_p]
mmseg.cache_words_get_iter_cache_word.restype  = c_char_p



cal.
########################################
# Python API
########################################

def dict_load_chars(path):
    res = mmseg.mmseg_load_chars(path)
    if res == 0:
        return False
    return True

def dict_load_words(path):
    res = mmseg.mmseg_load_words(path)
    if res == 0:
        return False
    return True

def dict_load_defaults():
#    mmseg.mmseg_load_chars(join(dirname(__file__), 'data', 'chars.dic'))
    mmseg.mmseg_load_words(join(dirname(__file__), 'data', 'library.dic'))


def get_default_library_path():
    return LIBRARY_PATH

def get_default_cache_path():
    return CACHE_PATH


class Algorithm(object):
    def __init__(self, text):
        """\
        Create an Algorithm instance to segment text.
        """
        self.algor = mmseg.mmseg_algor_create(text, len(text))
        self.destroied = False

    def __iter__(self):
        """\
        Iterate through all tokens. Note the iteration has
        side-effect: an Algorithm object can only be iterated
        once.
        """
        while True:
            tk = self.next_token()
            if tk is None:
                raise StopIteration
            yield tk
    
    def next_token(self):
        """\
        Get next token. When no token available, return None.
        """
        if self.destroied:
            return None
        
        tk = mmseg.mmseg_next_token(self.algor)
        if tk.length == 0:
            # no token available, the algorithm object
            # can be destroied
            self._destroy()
            return None
        else:
            return tk

    def _destroy(self):
        
        if not self.destroied:
            mmseg.mmseg_algor_destroy(self.algor)
            self.destroied = True

    def __del__(self):
        self._destroy()


class Update_words(object):
    """Update Word Library Dict"""
    def __init__(self,library_path=LIBRARY_PATH):
        self.obj = mmseg.update_words_init(library_path)
        self.cache_path = CACHE_PATH

    def auto_run(self):
        self.incr_words_count_from_cache()
        self.write_file()

        cache_words_obj = Cache_words(self.cache_path)
        cache_words_obj.clean()

    def set_cache_path(self,cache_path):
        self.cache_path = cache_path

    def incr_words_count_from_cache(self):
        mmseg.update_words_incr_words_count_from_cache(self.obj,self.cache_path)

    def write_file(self):
        mmseg.update_words_write_file(self.obj)

    def _destroy(self):
        mmseg.update_words_destroy(self.obj)

    def __del__(self):
        self._destroy()


class Cache_words(object):
    """Cache word Library Dict"""
    def __init__(self,path=get_default_cache_path()):
        self.obj = mmseg.cache_words_init(path)

    def auto_run(self,words):
        self.add_words(words)
        self.write_file()


    def add_words(self,words):
        """add all to cache"""
        for word in words:
            mmseg.cache_words_add_word(self.obj,word)

    def write_file(self):
        """write to cache"""
        mmseg.cache_words_write_file(self.obj)

    def get_cache_words(self):
        content = mmseg.cache_words_get_cache_words()
        return content.split("\n")


    def clean(self):
        """flush cache content"""
        mmseg.cache_words_clean(self.obj);

    def _destroy(self):
        """delete obj"""
        mmseg.cache_words_destroy(self.obj)

    def __del__(self):
        self._destroy()
