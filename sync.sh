#!/bin/sh
mysqldump -uroot -p1 tuokouerchu > tuokouerchu.sql
svn ci -m "`date`"

