#!/usr/local/bin/python
#coding:utf-8
#caculte left border stability
#also filter according to border stab
import math
import sys
import dna_segment


"""
function : static left words
           left_dict record all left words and frequency of one word,
           for example, left_dict["ATCCG"] = {"AT":12,"GGGGG":11,.....}
input: split_words, a segmented sequence
output: left_dict, record all left words of a word
"""
def StaticLeftWord(split_words, left_dict):
    for i in range(1,len(split_words)):
        cur_word = split_words[i]
        pre_word = split_words[i-1]
        left_dict.setdefault(cur_word,{})
        if left_dict[cur_word].has_key(pre_word):
            left_dict[cur_word][pre_word] = left_dict[cur_word][pre_word] + 1
        else:
            left_dict[cur_word][pre_word] = 1
    return 0


"""
function : static right words
           left_dict record all right words and frequency of one word,
           for example, right_dict["ATCCG"] = {"AT":12,"GGGGG":11,.....}
input: split_words, a segmented sequence
output: right_dict, record all right words of a word
"""
def StaticRightWord(split_words, right_dict):
    for i in range(0,len(split_words)-1):
        cur_word = split_words[i]
        next_word = split_words[i+1]
        right_dict.setdefault(cur_word,{})
        if right_dict[cur_word].has_key(next_word):
            right_dict[cur_word][next_word] = right_dict[cur_word][next_word] + 1
        else:
            right_dict[cur_word][next_word] = 1
    return 0


"""
function: caculate border stability, definition: -1*sum(p(Wi)*log[p(Wi)])/log(n),
          here n is unique word number in W, log is base 2
          p(Wi)=C(Wi)/C(W), C is word occurrence
input: word
input: border_word_list, record the border words and frequency of input word
output: border_stab, border stability of word
"""
def CaculateBorderStab(word, border_word_list, border_stab):
    #step 1, get all frequency of border word occurrence
    sum_all = 0
    for item in border_word_list:
        sum_all = sum_all + border_word_list[item]

    #step 2, get border stability
    info_sum = 0
    for item in border_word_list:
        prob = float(border_word_list[item])/sum_all
        info = -1*prob*math.log(prob,2)
        info_sum = info_sum + info

    #uniform
    norm_factor = math.log(len(one_word_list),2)
    if norm_factor != 0:
        border_stab[word] = info_sum/math.log(len(one_word_list),2)
    else:
        border_stab[word] = 0

if __name__=='__main__':
    if len(sys.argv) != 3 :
        print "please input the dict  file name and data file name"
        sys.exit()
    seg = dna_segment.DNASegment()
    seg.initial_dict(sys.argv[1])

    right_prob_select = {}

    left_dict = {}
    right_dict = {}
    #step 1, static left words
    data_file = open(sys.argv[2],'r')
    for line in data_file:
        line = line.strip()
        line = line.replace(" ","")
        seg_sequence = seg.mp_seg(line)
        split_words = seg_sequence.split('\ ')
        StaticLeftWord(split_words, left_dict)
        StaticRightWord(split_words, right_dict)
    data_file.close()

    #step 2, caculate left/right border stability
    #select the less one as the final border stability of one word
    left_stab = {}
    #caculate left stability
    for item in left_dict:
        one_word_list = left_dict[item]
        CaculateBorderStab(item, one_word_list, left_stab)

    right_stab = {}
    #caculate right stability
    for item in right_dict:
        one_word_list = right_dict[item]
        CaculateBorderStab(item, one_word_list, right_stab)

    #select less one
    border_stab = {}
    for item in left_stab:
        if right_stab.has_key(item):
            if left_stab[item] < right_stab[item]:
                border_stab[item] = left_stab[item]
            else:
                border_stab[item] = right_stab[item]

    #step 3, filter the dict
    #sort and select top n
    word_stab_list = sorted(border_stab.iteritems(),key=lambda d:d[1], reverse=True)
    word_select = {}
    threshold = 0.5 #select threshold, experienced value

    top_n = len(word_stab_list)*threshold
    for item in word_stab_list:
        #print item[0] + "\t" + str(item[1])
        if item[1] > 0.5:
            word_select[item[0]] = 1

    #filter dict
    dict_file = open(sys.argv[1],'r')
    for line in dict_file:
        line = line.strip()
        word = line.split("\t")[0]
        prob = line.split("\t")[1]
        if word_select.has_key(word) or len(word)<=3:
            print word + "\t" + prob
