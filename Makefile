WARNING = -Wall -Wshadow
ERROR = -Wvla
GCC = gcc -std=c99 -pedantic $(WARNING) $(ERROR) 
EXEC = pa3
OBJS = *.c

all: $(OBJS)
	$(GCC) -O3 $(OBJS) -o $(EXEC)

$(EXEC): $(OBJS)
	$(GCC) $(OBJS) -o $(EXEC)

%.o: %.c 
	$(GCC) -c $<

testall: test3

test1: $(EXEC)
	./$(EXEC) examples/5_4.b testOutputs/textFile5_4.txt testOutputs/fastestTimes5_4.bin testOutputs/fastestPath5_4.bin

test100: $(EXEC)
	./$(EXEC) 100_100.b testOutputs/textFile100_100.txt testOutputs/fastestTimes100_100.bin testOutputs/fastestPath100_100.bin

test50: $(EXEC)
	./$(EXEC) 50_50.b testOutputs/textFile50_50.txt testOutputs/fastestTimes50_50.bin testOutputs/fastestPath50_50.bin

test10: $(EXEC)
	./$(EXEC) 10_10.b testOutputs/textFile50_50.txt testOutputs/fastestTimes50_50.bin testOutputs/fastestPath50_50.bin


test2: $(EXEC)
	./$(EXEC) examples/5_5.b testOutputs/textFile5_5.txt testOutputs/fastestTimes5_5.bin testOutputs/fastestPath5_5.bin

test3: $(EXEC)
	./$(EXEC) examples/7_7.b testOutputs/textFile7_7.txt testOutputs/fastestTimes7_7.bin testOutputs/fastestPath7_7.bin

memory: $(EXEC)
	valgrind --log-file=log1 --leak-check=full --track-origins=yes ./$(EXEC) examples/5_5.b testOutputs/textFile5_5.txt testOutputs/fastestTimes5_5.bin testOutputs/fastestPath5_4.bin

memory3: $(EXEC)
	valgrind --log-file=log3 --leak-check=full ./$(EXEC) examples/7_7.b testOutputs/textFile7_7.txt testOutputs/fastestTimes7_7.bin testOutputs/fastestPath7_7.bin


memory100: $(EXEC)
	valgrind --log-file=log100 --leak-check=full ./$(EXEC) 100_100.b testOutputs/textFile100_100.txt testOutputs/fastestTimes100_100.bin testOutputs/fastestPath100_100.bin


clean: # remove all machine generated files
	rm -f pa3 *.o log*



