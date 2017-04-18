#include <cstdio>
#include <vector>
#include <functional>
#include <string>

/*

The main idea here is to make a "stacker":

A simple instruction interpreter that only deals
with basic arithmetic

*/

/* Not yet in use */
std::vector<std::function<int()>> opstack;

int InterpretComm ( char **args, int length );
int UtoI ( const std::string& data );

int main ( int argc, char *argv[] ) {


	auto PrintArgs = [&]() -> void {
		for ( size_t i = 0; i < argc; ++i ) {
			std::printf( "argv[%d] = %s\n", i, argv[i] );
		}
	};

	PrintArgs();

	std::printf( "Result: %d", InterpretComm( ++argv, argc - 1 ) );

	return 0;
}

/* This function will be recursive, and will handle a variable length arithmetic operation */
int InterpretComm ( char **args, int length ) {
	/* Define some basic arithmetic operations using lambda functions */
	auto add = [=]( int arg1, int arg2 ) -> int {
		return arg1 + arg2;
	};

	auto sub = [=]( int arg1, int arg2 ) -> int {
		return arg1 - arg2;
	};

	auto mult = [=]( int arg1, int arg2 ) -> int {
		return arg1 * arg2;
	};

	auto div = [=]( int arg1, int arg2 ) -> int {
		return arg1 / arg2;
	};

	/* If the args array is empty... */
	//if ( !length ) {
	//return 0;
	//}

	for ( size_t i = 1; i < length; ++i ) {
		if ( args[i] == "+" ) {
			std::printf( "adding..." );
			return add( UtoI( args[0] ), InterpretComm( ++args, length - 1 ) );
		} else if ( args[i] == "-" ) {
			std::printf( "subtracting..." );
			return sub( UtoI( args[0] ), InterpretComm( ++args, length - 1 ) );
		} else if ( args[i] == "*" ) {
			std::printf( "multiplying..." );
			return mult( UtoI( args[0] ), InterpretComm( ++args, length - 1 ) );
		} else if ( args[i] == "/" ) {
			std::printf( "dividing..." );
			return div( UtoI( args[0] ), InterpretComm( ++args, length - 1 ) );
		}
	}
}

int UtoI ( const std::string& data ) {
	int val = 0, pv = 1;
	for ( size_t i = data.length() - 1; i >= 0; --i, pv *= 10 ) {
		val += ( data[i] - '0' ) * pv;
	}
	std::printf( "Val: %d", val );
	return val;
}