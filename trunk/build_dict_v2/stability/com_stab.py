#!/usr/local/bin/python
#coding:utf-8
#compare two dict's segment

import math
import sys
import dna_segment

def get_probility(sequence,seg_ge1, seg_ge2):
    seg_sequence = seg_ge1.mp_seg(sequence)
    split_words = seg_sequence.split('\ ')
    #print split_words
    word_pos1 = {}
    pos_left = 0
    pos_right = 0
    for word in split_words:
        pos_right = pos_left + len(word)
        word_pos1[pos_left] = pos_right
        pos_left = pos_right

    #print word_pos1

    #segment sequence by dict2
    sequence_sub = sequence
    #print sequence_sub
    seg_sequence = seg_ge2.mp_seg(sequence_sub)
    split_words = seg_sequence.split('\ ')
    #print split_words

    word_pos2 = {}
    pos_left = 0
    pos_right = 0
    for word in split_words:
        pos_right = pos_left + len(word)
        word_pos2[pos_left] = pos_right
        pos_left = pos_right

    #print word_pos2
    same_item_length = 0
    for item in word_pos1:
        if word_pos2.has_key(item):
            if word_pos2[item] == word_pos1[item]:
                same_item_length = same_item_length + (word_pos1[item] - item)

    if same_item_length == len(sequence):
        stability=1
    else:
        stability = float(same_item_length)/(len(sequence))

    return stability

if __name__=='__main__':
    if len(sys.argv) != 4 :
        print "please input two dict and one test data file name"
        sys.exit()

    seg1 = dna_segment.DNASegment()
    seg1.initial_dict(sys.argv[1])

    seg2 = dna_segment.DNASegment()
    seg2.initial_dict(sys.argv[2])

    filename = sys.argv[3]
    data_file = open(filename,'r')

    stability_sum = 0
    line_num = 0
    for line in data_file:
        sequence = line.replace("\n","")
        #print sequence
        stability = get_probility(sequence, seg1, seg2)
        stability_sum = stability_sum + stability
        line_num = line_num + 1
        #print stability

    avg_stability = stability_sum/line_num
    print "average stability : " + str(avg_stability)
