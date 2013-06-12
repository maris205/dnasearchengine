#!/usr/local/bin/python
#coding:utf-8
#filter low prob word that will never appear
#if a word could be divided into more words,
#which means if probability of less than the mutltiple of its parts
import math
import sys
import dna_segment
if __name__=='__main__':
    if len(sys.argv) != 2 :
        print "please input dict file name"
        sys.exit()

    filename = sys.argv[1]
    seg = dna_segment.DNASegment()
    seg.initial_dict(filename)

    data_file = open(filename,'r')
    for line in data_file:
        line = line.strip()
        key = line.split("\t")[0]
        prob = line.split("\t")[1]

        seg_sequence = seg.mp_seg(key)
        split_words = seg_sequence.split('\ ')
        if len(split_words) == 1:
            print key + "\t" + prob
