use language to build the DNA dictionary
Here we only discus the Linux environment.

Package structures:

The directory

dna_data/  : the DNA data, here we use the genomes of Schizosaccharomyces.
pre_process/ : simple pre process the DNA, just divide each DNA letters by space and write several lines into one line. Meet the input requirement of SRILM
build_dict /  : filter the n-gram segmentation and get the DNA vocabulary . Here we only use the frequency filter.
get_prob/  : get the probability of each ¡°words¡± in DNA vocabulary.
segmentation/ : DNA segmentation function
stability/ : segmentation stability test

You should cd each directory and make. In ¡®get_prob¡¯, please set the lib and include path of SRILM in its Makefile properly.

Tools and data

1 Language model tools. Please install the statistical language tools SRILM. (http://www.speech.sri.com/projects/srilm/) . It seems that install this source code is not an very easy mission. So please seek help in its forums if meeting any problems : )

2 Experimental data. Here we use a short genome as experimental data to show our work.(For human genomes, train the 15-ngram model will need more than 30G memories.  Short genomes will need few memory, still wish you have a good computer¡­¡­)Here we select Schizosaccharomyces, It could be downloaded from ftp://ftp.ncbi.nih.gov/genomes/Schizosaccharomyces_pombe_OLD/.  We get three data files from three directory. (NC_003421.fna, NC_003423.fna, NC_003424.fna). we have put these data in dna_data/ of this package.


Experiments

1 merge the data.
In ¡®dna_data/¡¯,merge three DNA data files, run
cat *.fna > Schizosaccharomyces.fasta
then cp the file ¡®Schizosaccharomyces.fasta¡¯ to ¡®pre_process¡¯

2 pre process , divide each letter by space, in ¡®pre_process¡¯,run
./convert  Schizosaccharomyces.fasta > Schizosaccharomyces.fasta.seg
Then cp the ¡®Schizosaccharomyces.fasta.seg¡¯ to the bin (execute file) directory of SRILM.

3 build the language model using the SRILM, here we build 9-gram model. So the maximal word length will set as 9. Higher order model will use much more memories.
In SRILM execute file directory
A. Count the n-gram, run
./ngram-count -text Schizosaccharomyces.fasta.seg -order 9 -write Schizosaccharomyces.fasta.seg.count  -no-sos  -no-eos
B. Build the language model, run
./ngram-count -read Schizosaccharomyces.fasta.seg.count -order 9 -lm Schizosaccharomyces.fasta.seg.lm

Here we get two files, cp the ¡®Schizosaccharomyces.fasta.seg.count¡¯ to ¡®build_dict¡¯, cp the ¡®Schizosaccharomyces.fasta.seg.lm¡¯  to  ¡®get_prob¡¯.


4 build the vocabulary, in ¡®build_dict¡¯, run
./build_dict Schizosaccharomyces.fasta.seg.count > Schizosaccharomyces.fasta.seg.count.dict
Then cp Schizosaccharomyces.fasta.seg.count.dic¡¯  to ¡®get_prob¡¯

5 get the probability of each word, in ¡®get_prob¡¯,run
./get_prob Schizosaccharomyces.fasta.seg.lm Schizosaccharomyces.fasta.seg.count.dict > dict.txt

Here the dict.dat is just the dictionary with probability we need in segmentation operation. Then cp ¡®dict.txt¡¯ to ¡®segmentation¡¯ and  ¡®seg_stability¡¯

6 run segmentation test
In ¡®segmentation¡¯, just run
./test , it¡¯s a simple example to segment a short sequence.
In seg_stability, run
./stability dict.txt Schizosaccharomyces_10000.dat
We will get the stability for each test data line, test data Schizosaccharomyces_10000.dat is obtained from Schizosaccharomyces genomes.
