all :
	cd src && make; cd 4value && make; chmod u+x+w+r ../../latc

clean :
	cd src && make clean; cd 4value && make clean