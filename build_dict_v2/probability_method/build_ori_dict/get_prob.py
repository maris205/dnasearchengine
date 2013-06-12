#!/usr/bin/env python
import sys
import math

MAX_WORD_LENGTH = 9
#get prob according to count file
# add 1 smooth
def get_prob(freq_dict,word_length):
    word_num = 4**word_length  # all possible word number
    local_dict = {}
    freq_sum = 0
    for item in freq_dict:
        if len(item) == word_length:
            freq = freq_dict[item] + 1
            local_dict.setdefault(item, freq)
            freq_sum = freq_sum + freq_dict[item]
    #out put
    for item in local_dict:
        prob = math.log(float(local_dict[item])/(freq_sum+word_num))
        print item + "\t" + str(prob)

if __name__=="__main__":
    if len(sys.argv) != 2 :
        print "please input the count file name"
        sys.exit()

    filename = sys.argv[1]
    data_file = open(filename,'r')
    freq_dict = {}

    for line in data_file:
        line = line.strip()
        word = line.split("\t")[0]
        word = word.replace(" ","")
        freq = int(line.split("\t")[1])
        #print word
        #print freq
        freq_dict.setdefault(word,freq)

    for i in range(1, MAX_WORD_LENGTH+1):
        get_prob(freq_dict,i)
