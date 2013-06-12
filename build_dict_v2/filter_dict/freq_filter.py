#!/usr/local/bin/python
#coding:utf-8
#also filter according to prob/freq
#select top threshold_percent word for same length
import math
import sys

threshold_percent = 0.9

if __name__=='__main__':
    if len(sys.argv) != 2 :
        print "please input the dict  file name"
        sys.exit()

        #filter dict
    dict_file = open(sys.argv[1],'r')
    word_dict = {}
    for line in dict_file:
        line = line.strip()
        word = line.split("\t")[0]
        prob = line.split("\t")[1]
        word_length = len(word)
        word_dict.setdefault(word_length,{})
        word_dict[word_length][word] = float(prob)

    #sort and out put
    for item in word_dict:
        word_list = sorted(word_dict[item].iteritems(),key=lambda d:d[1],reverse=True)
        if item > 3:
            select_num = int(threshold_percent*len(word_list))
        else:
            select_num = int(len(word_list)) + 1
        for select_item in word_list[0:select_num]:
            print select_item[0] + "\t" + str(select_item[1])

