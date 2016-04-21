CXX=g++ -std=gnu++11
SUB_DIR=erode_dilate featuresMatch filter MerryChristmas outline stiching

.PHONY:all
all:
	@for n in $(SUB_DIR);do $(MAKE) -C $$n;done
	
.PHONY:clean
clean:
	@for n in $(SUB_DIR);do $(MAKE) -C $$n clean;done

