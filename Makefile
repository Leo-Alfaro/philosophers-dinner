# compile deadlock code
dinner-deadlock: main.c philosopher.c
	gcc main.c philosopher.c -o dinnerLock -lpthread

# compile fixed code
dinner-fixed: main.c philosopher.c
	gcc main.c philosopher_fix.c -o dinner -lpthread 

# run deadlock .exe
run-deadlock: dinner-deadlock
	./dinnerLock $(N)

# run fixed .exe
run-fixed: dinner-fixed
	./dinner $(N)

# clean .exe
clean:
	rm -f dinner dinnerLock