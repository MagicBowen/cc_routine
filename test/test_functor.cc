#include "catch2/catch.hpp"
#include <stdio.h>

#define BEGIN()  void operator()() { switch(next_line) { case 0:
#define YIELD()  next_line=__LINE__; break; case __LINE__:
#define END()    }} int next_line=0

struct Coroutine {
	int n;
    int result;

	Coroutine(int n) : n(n) {}
	
	BEGIN();
	while(n--) {
        result = n;
        YIELD();
    }
	END();
};

SCENARIO("should loop from 2 to 0") {
    Coroutine co{3};

    co();
    REQUIRE(2 == co.result);

    co();
    REQUIRE(1 == co.result);

    co();
    REQUIRE(0 == co.result);

    co();
    REQUIRE(0 == co.result);
}


struct Coroutine1 {
	int i{0};

	BEGIN();
    printf("i = %d\n", i++);
    YIELD();
    printf("i = %d\n", i++);
    YIELD();
    printf("i = %d\n", i++);
    YIELD();    
	END();
};

SCENARIO("should print from 0 to 2") {
    Coroutine1 co;

    co();
    co();
    co();
    co(); // should do nothing!!!
    REQUIRE(3 == co.i);
}