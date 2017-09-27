.PHONY: clean

CXX_FLAGS=-std=c++11 -Wall -Werror -O2 -g -fno-exceptions -fno-rtti

atomic_flag_spinlock: atomic_flag_spinlock.cc
	$(CXX) $(CXX_FLAGS) atomic_flag_spinlock.cc -o atomic_flag_spinlock
clean:
	rm -f atomic_flag_spinlock

