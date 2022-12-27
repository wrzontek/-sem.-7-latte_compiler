all :
	cd src/latte && make; cd ../4value && make; chmod u+x+w+r ../../latc

clean :
	cd src/latte && make clean; cd ../4value && make clean