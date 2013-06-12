#!/usr/local/bin/python
#coding:utf-8
import math
import sys
import dna_segment

#sequence, full sequence ; pos ,0:left,1,right; del_num, del letter number
def get_probility(sequence,seg_ge,pos,del_num):
    seg_sequence = seg_ge.mp_seg(sequence)
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

    # get sub sequence
    if pos == 0:
        sequence_sub = sequence[del_num:len(sequence)]
    else:
        sequence_sub = sequence[0:len(sequence)-del_num]

    #print sequence_sub
    seg_sequence = seg_ge.mp_seg(sequence_sub)
    split_words = seg_sequence.split('\ ')
    #print split_words

    word_pos2 = {}

    if pos == 0:
        pos_left = del_num
        pos_right = 0
    else:
        pos_left = 0

    for word in split_words:
        pos_right = pos_left + len(word)
        word_pos2[pos_left] = pos_right
        pos_left = pos_right

    #print word_pos2
    same_item_num = 0
    for item in word_pos1:
        if word_pos2.has_key(item):
            if word_pos2[item] == word_pos1[item]:
                same_item_num = same_item_num + 1

    if same_item_num == len(word_pos2):
        stability=1
    else:
        stability = float(same_item_num)/(len(word_pos2)-1)

    return stability

if __name__=='__main__':
    if len(sys.argv) != 3 :
        print "please input the dict and test data file name"
        sys.exit()

    seg1 = dna_segment.DNASegment()
    seg1.initial_dict(sys.argv[1])

    filename = sys.argv[2]
    data_file = open(filename,'r')

    stability_sum = 0
    line_num = 0
    for line in data_file:
        sequence = line.replace("\n","")
        #print sequence
        for i in range(1,13):
            stability = get_probility(sequence, seg1,0,i)
            stability = get_probility(sequence, seg1,1,i)
            stability_sum = stability_sum + stability
            line_num = line_num + 1
            #print stability

    avg_stability = stability_sum/line_num
    print "average stability : " + str(avg_stability)
