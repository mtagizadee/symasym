
# Run program guideline
- [ ] If you do not have dist folder in the root of the project then create it: `mkdir dist`
- [ ] Makefile is saved in the src folder, so in order to run it you should change your direcotry to src folder: `cd src`
- [ ] Run make command which will compile the code. IMPORTANT, THE OUTPUT PROGRAM IS SAVED IN THE DIST DIRECTORY: `make`
- [ ] Change your directory to dist to run program: `cd ../dist`
- [ ] Run the program, IMPORTANT, GENERATED IMAGES ARE STORED IN THE DIST DIRECORY: `./symasym` 

# Clean program guideline
- [ ] Change your directory again to src folder since makefile is there.
- [ ] If you want to delete just output programs then run: `make clean`. Or if you want to delete generated images as well then run: `make clean-all`