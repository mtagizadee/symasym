# output file 
o := symasym

# destination folder
dest := ../dist

main: 
	gcc main.c random/random.c symasym/symasym.c config/config.c -o ${o}.out -Wall && mv ${o}.out ${dest} && cd ${dest} && mv ${o}.out ${o}

clean:
	cd ${dest} && rm -r ${o}

clean-all: clean 
	cd ${dest} && rm -r *.bmp