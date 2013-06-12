#!/usr/bin/env python
import sys
#pre process the data

if __name__=="__main__":
    if len(sys.argv) != 2:
        print "please input filename"
        sys.exit()
    filename = sys.argv[1]
    data_file = open(filename, 'r')
    text = "";
    for line in data_file:
        line = line.strip()
        if line.find(">") != 0:
            text = text + line
            if len(text) > 30000:
                text = " ".join(text)
                text = text.strip()
                print text
                text = ""
    #last line
    if len(text) <= 30000:
        text = " ".join(text)
        text = text.strip()
        print text
