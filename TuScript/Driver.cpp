#include <cstdio>
#include <vector>
#include <functional>
#include <string>

/*

The main idea here is to make a "stacker":

A simple instruction interpreter that only deals
with basic integer arithmetic

*/

static std::vector<int> numstack;
static std::vector<std::function<int( int, int )>> opstack;

auto TuAdd = [=]( int arg1, int arg2 ) -> int {
	return arg1 + arg2;
};

auto TuSub = [=]( int arg1, int arg2 ) -> int {
	return arg1 - arg2;
};

auto TuMult = [=]( int arg1, int arg2 ) -> int {
	return arg1 * arg2;
};

auto TuDiv = [=]( int arg1, int arg2 ) -> int {
	return arg1 / arg2;
};

int InterpretComm ( char **args, int length );

int main ( int argc, char *argv[] ) {
	std::printf( "Result: %d\n", InterpretComm( ++argv, --argc ) );
	return 0;
}

int PopNum () {
	if ( numstack.empty() ) return 0;
	int val = numstack.back();
	numstack.pop_back();
	return val;
}

std::function<int( int, int )> PopOp () {
	std::function<int( int, int )> func = opstack.back();
	opstack.pop_back();
	return func;
}

int InterpretComm ( char **args, int length ) {
	for ( size_t i = 0; i < length; ++i ) {
		if ( !strcmp( args[i], "+" ) ) {
			opstack.push_back( TuAdd );
		} else if ( !strcmp( args[i], "-" ) ) {
			opstack.push_back( TuSub );
		} else if ( !strcmp( args[i], "*" ) ) {
			numstack.push_back( TuMult( PopNum(), atoi( args[i++ + 1] ) ) );
		} else if ( !strcmp( args[i], "/" ) ) {
			numstack.push_back( TuDiv( PopNum(), atoi( args[i++ + 1] ) ) );
		} else { /* args[0] is a number */
			numstack.push_back( atoi( args[i] ) );
		}
	}

	int result;
	while ( !opstack.empty() ) {
		int arg2 = PopNum();
		int arg1 = PopNum();
		numstack.push_back( PopOp()( arg1, arg2 ) );
	}
	result = PopNum();

	return result;
}