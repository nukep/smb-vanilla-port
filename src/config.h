// Compiler-time flag for now. This should be runtime.
//#define SMB2J_MODE

//#define USE_MOVIE "/path/to/movie"
//#define USE_MOVIE_SKIPAHEAD 100
//#define USE_MOVIE_COMPARERAM
//#define USE_MOVIE_LOAD_RAM_AFTER_SKIPAHEAD


#ifndef USE_MOVIE_SKIPAHEAD
#	define USE_MOVIE_SKIPAHEAD 0
#endif

#ifndef SMB2J_MODE
#	define SMB1_MODE
#endif
