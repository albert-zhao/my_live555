test_time: ../src/timevalue.cc test_timeval.cc
	g++ -std=c++11 -I ../include $^ -g -o $@

test_delayqueue: ../src/timevalue.cc ../src/delayqueue.cc test_delayqueue.cc
	g++ -std=c++11 -I ../include $^ -g -o $@
.PHONY: clean
clean:
	rm -f test_time test_delayqueue