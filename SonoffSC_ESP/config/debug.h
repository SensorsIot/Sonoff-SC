#ifdef SERIALDEBUG
    #define DEBUG_MSG(...) Serial.printf( __VA_ARGS__ )
#else
    #define DEBUG_MSG(...)
#endif
