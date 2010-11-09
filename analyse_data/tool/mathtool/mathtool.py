# -*- coding: utf-8 -*-

import sys
import os
from ctypes import *
from os.path import join, dirname, abspath, exists
import glob


if sys.platform == 'win32':
    ext = 'dll'
else:
    ext = 'so'

"""以后我们都假设为*nix平台"""

libs = glob.glob("cpp/lib*so")
if(libs):
    lib = os.path.basename(libs[0])
else:
    lib = "libwordseg.%s" % ext

try:
    path = os.path.join(dirname(__file__),'cpp',lib)
    mod_mathtool = cdll.LoadLibrary(path)
except:
    print("No such path:%s" % path)
    sys.exit(0)


########################################
# Init function prototypes
########################################
mod_mathtool.sum.argtypes = [POINTER(c_double),c_long]
mod_mathtool.sum.restype  = c_double 

mod_mathtool.geometric_avarage.argtypes = [POINTER(c_double),c_long]
mod_mathtool.geometric_avarage.restype  = c_double 

mod_mathtool.arithmetic_average.argtypes = [POINTER(c_double),c_long]
mod_mathtool.arithmetic_average.restype  = c_double 

mod_mathtool.standard_deviation.argtypes = [POINTER(c_double),c_long]
mod_mathtool.standard_deviation.restype  = c_double 

mod_mathtool.variance.argtypes = [POINTER(c_double),c_long]
mod_mathtool.variance.restype  = c_double 

########################################
# Python API
########################################
def dec(fn):
    def func(self,array):
        len = array.__len__()
        cArray = (c_double*len)()
        cArray[:] = array
        return fn(self,cArray)
    return func

class Mathtool:
#    def turn_c_type(self,array):
#        if(isinstance(array,list) | isinstance(array,tuple)):
#            len = array.__len__()
#            cArray = (c_double*len)()
#            cArray[:] = array
#            return cArray
#        else:
#            return array

    @dec
    def sum(self,array):
        len = array.__len__()
        return mod_mathtool.sum(array,len)

    @dec
    def geometric_avarage(self,array):
        len = array.__len__()
        return mod_mathtool.geometric_avarage(array,len)

    @dec
    def arithmetic_average(self,array):
        len = array.__len__()
        return mod_mathtool.arithmetic_average(array,len)

    @dec
    def standard_deviation(self,array):
        len = array.__len__()
        return mod_mathtool.standard_deviation(array,len)

    @dec
    def variance(self,array):
        len = array.__len__()
        return mod_mathtool.variance(array,len)

    def __del__(self):
        pass

    def __str__(self):
        return self.__name__
