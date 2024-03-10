#include <stdio.h>
#include <unistd.h>
#include <string>
#include <nng/nng.h>
#include <nng/protocol/pubsub0/pub.h>
#include <nng/protocol/pubsub0/sub.h>

void fatal(const char *func, int rv) {
    fprintf(stderr, "%s: %s\n", func, nng_strerror(rv));
}

int client(const char *url) {
    nng_socket sock;
    int rv;

    if ((rv = nng_sub0_open(&sock)) != 0) {
	fatal("nng_sub0_open", rv);
    }

    // subscribe to everything (empty means all topics)
    if ((rv = nng_setopt(sock, NNG_OPT_SUB_SUBSCRIBE, "", 0)) != 0) {
	fatal("nng_setopt", rv);
    }
    
    if ((rv = nng_dial(sock, url, NULL, 0)) != 0) {
	fatal("nng_dial", rv);
    }

    std::string msg = "hello";
    
    for (;;) {
	char *buf = NULL;
	size_t sz;

	if ((rv = nng_recv(sock, &buf, &sz, NNG_FLAG_ALLOC)) != 0) {
	    fatal("nng_recv", rv);
	}

	printf("Client: Received %s\n", buf);	
	nng_free(buf, sz);
	int ret = nng_send(sock, (void *) msg.c_str(), msg.length(`), 0);
	printf("ret: %d\n ",ret);
	sleep(1);
    }
}

int main(const int argc, const char **argv) {
    client("ipc:///tmp/pubsub.ipc");
    return 0;
}
