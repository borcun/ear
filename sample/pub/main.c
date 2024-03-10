#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <nng/nng.h>
#include <nng/protocol/pubsub0/pub.h>
#include <nng/protocol/pubsub0/sub.h>

void fatal(const char *func, int rv) {
    fprintf(stderr, "%s: %s\n", func, nng_strerror(rv));
}

char *date(void) {
    time_t now = time(&now);
    struct tm *info = localtime(&now);
    char *text = asctime(info);
    text[strlen(text)-1] = '\0'; // remove '\n'

    return (text);
}

int server(const char *url)
{
    nng_socket sock;
    int rv;
    
    if ((rv = nng_pub0_open(&sock)) != 0) {
	fatal("nng_pub0_open", rv);
    }

    if ((rv = nng_listen(sock, url, NULL, 0)) < 0) {
	fatal("nng_listen", rv);
    }

    for (;;) {
	char *d = date();
	char *buf = NULL;
	size_t sz;

	printf("Server: Publishing date %s\n", d);

	if ((rv = nng_send(sock, d, strlen(d) + 1, 0)) != 0) {
	    fatal("nng_send", rv);
	}

	sleep(1);

	if ((rv = nng_recv(sock, &buf, &sz, NNG_FLAG_ALLOC)) != 0) {
	    fatal("nng_recv", rv);
	}

	printf("Server: Received %s\n", buf);
	nng_free(buf, sz);
    }
}

int main(const int argc, const char **argv) {
    server("ipc:///tmp/pubsub.ipc");
    return 0;
}
