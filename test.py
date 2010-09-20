#!/usr/bin/env python
# -*- coding:utf-8 -*-

#-------------------------------------------
# Auther      : free.Wang<freefis@gmail.com> 
# Licence     : License on GPL Licence
# Description :
#    ...
# Archieved   : Mar 2nd 2009  
#-------------------------------------------

url = "http://t.dianping.com/rss/beijing";   
url = "http://www.55tuan.com/feed-group-buy.xml"
url = "http://www.nuomi.com/feed/100010000"
url = "http://tuan.aibang.com/beijing/feed"
url =  "http://www.meituan.com/feed/beijing"
import feedparser
import time


dom = feedparser.parse(url)
print dom['headers']['date']
print dom['items'][0]['title']
print dom['items'][0]['link']
print dom['items'][0]['description']
print "="*10
print dom['encoding']
print dom['feed']['title']
print dom['feed']['link']
print dom['feed']['description']
