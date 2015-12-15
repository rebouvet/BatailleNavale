//Si nous sommes sous Windows
#if defined (WIN32)

    #include <winsock2.h>

    // typedef, qui nous serviront par la suite
    typedef int socklen_t;

// Sinon, si nous sommes sous Linux
#elif defined (linux)

    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>

    // Define, qui nous serviront par la suite
    #define INVALID_SOCKET -1
    #define PORT 1025
    #define SOCKET_ERROR -1
    #define closesocket(s) close (s)
	
    // De même
    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;

#endif
