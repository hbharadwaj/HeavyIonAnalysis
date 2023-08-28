g++ -std=c++0x ${1}.cc \
 -O2 -ansi -W -Wall -std=c++11 -Wshadow -m64 -Wno-shadow \
 -o ${1} \
 `root-config --cflags --ldflags --glibs ` -lEG -lz -lTMVA
