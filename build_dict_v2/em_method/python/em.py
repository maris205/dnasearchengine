#!/usr/local/bin/python
#coding:gbk
import math
import sys
import copy

word_dict_new={}
word_dict={}
letter_length = 1
g_max_word_length = 12

def getprob(sequence):
    s_left = []
    s_right = []
    for pos in range(0,len(sequence) + letter_length,letter_length):
        if pos == 0:
            s_left.append(1) #0
            continue

        if pos < g_max_word_length:
            max_word_length=pos
        else:
            max_word_length = g_max_word_length

        prob = 0
        for length  in range(letter_length, max_word_length+letter_length,letter_length):
            word = sequence[pos-length:pos]
            if word_dict.has_key(word):
                prob = prob + (word_dict[word]*s_left[(pos-length)/letter_length])
            else:
                return -1

        s_left.append(prob)
    print s_left

    #get s_right
    for pos in range(len(sequence),-1*letter_length, -1*letter_length):
        if pos == len(sequence) :
            s_right.append(1) #0
            continue

        if len(sequence)-pos < g_max_word_length:
            max_word_length = len(sequence)-pos
        else:
            max_word_length = g_max_word_length

        prob = 0
        for length  in range(letter_length,max_word_length+letter_length,letter_length):
            word = sequence[pos:pos+length]
            if word_dict.has_key(word):
                prob = prob + word_dict[word]*s_right[(len(sequence) - (pos+length))/letter_length]
                increase = s_left[pos/letter_length]*word_dict[word]*s_right[(len(sequence) - pos-length)/letter_length]/s_left[-1]
                if increase < 1:
                    #print word + " increase " + str(increase)
                    word_dict_new.setdefault(word,0)
                    word_dict_new[word] = word_dict_new[word] + increase
                else:
                    return -1
            else:
                return -1
        s_right.append(prob)
    print s_right
    return 0

if __name__=='__main__':
    if len(sys.argv) != 3 :
        print "please input the dict file name and data file name"
        sys.exit()

    dict_file_name = sys.argv[1]
    filename = sys.argv[2]
    dict_file = open(dict_file_name, 'r')


    for line in dict_file:
        sequence = line.replace('\n','')
        key = sequence.split('\t')[0]
        value = float(sequence.split('\t')[1])
        word_dict[key] = value

    print word_dict['A']
    print "load dict success!!"
    data_file = open(filename,'r')
    sys.stdout.flush()
    for circle in range(1):
        line_num = 0
        for line in data_file:
            if (line_num%100000) == 0:
                print 'line number ' + str(line_num)
                sys.stdout.flush()
            sequence = line.replace("\n","")
            #print sequence
            i = getprob(sequence)
            if i != -1:
                line_num = line_num + 1
        data_file.seek(0)
        print word_dict_new
        print "____________________prob_________________" + str(line_num)
        for item in word_dict_new:
            word_dict_new[item] = word_dict_new[item]/line_num

        #dict_list_new=sorted(word_dict_new.items(),key=lambda d:d[1], reverse=True)
        #for key,value in dict_list_new:
        #    print key + '\t'+ str(value)

        #caculate stardard error
        error_sum = 0
        for item in word_dict_new:
            error_sum = error_sum + abs(word_dict_new[item] - word_dict[item])
        #exchange dict
        error_mean = error_sum/line_num
        print 'mean error ' + str(error_mean)

        word_dict = copy.deepcopy(word_dict_new)
        word_dict_new.clear()

    print "the last dict_________________________________"
    word_dict_new = copy.deepcopy(word_dict)
    dict_list_new=sorted(word_dict_new.items(),key=lambda d:d[1], reverse=True)
    for key,value in dict_list_new:
        print key + '\t'+ str(value)
