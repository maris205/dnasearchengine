#!/usr/bin/env python
#coding=gbk
import sys

word_dict = {}

def ngram_count(line,n_gram):
    word_list = line.split(' ')
    if len(word_list) >= n_gram :
        #正向切分
        for begin_pos in range(0,len(word_list)-n_gram+1):
            word = "".join(word_list[begin_pos:begin_pos+n_gram])
            #print word
            word_dict.setdefault(word,0)
            word_dict[word] = word_dict[word] + 1

#将分词后的字符串进行n-gram切分
if __name__=="__main__":
    if len(sys.argv) != 3 :
        print "please input filename and n of n-gram"
        sys.exit(0)

    filename = sys.argv[1]
    n_gram = int(sys.argv[2])

    datafile = open(filename,'r')
    ngram_file = open(filename+'.gram-'+str(n_gram),'w')

    for line in datafile:
        line = line.strip()
        ngram_count(line,n_gram)

    #统计输出
    #print word_dict
    word_list = sorted(word_dict.iteritems(), key=lambda d:d[1], reverse=True)
    #print word_list
    for word_freq in word_list:
        ngram_file.write(word_freq[0] + "\t" + str(word_freq[1])+"\n")
