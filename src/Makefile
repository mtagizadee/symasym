# output file 
o := symasym

# destination folder
dest := ../dist

main: 
	@if [ ! -d $(dest) ]; then mkdir -p $(dest); fi
	gcc main.c random/random.c symasym/symasym.c config/config.c -o ${o}.out -Wall && mv ${o}.out ${dest} && cd ${dest} && mv ${o}.out ${o}

clean:
	cd ${dest} && rm -r ${o}

clean-img: 
	cd ${dest} && rm -r *.bmp