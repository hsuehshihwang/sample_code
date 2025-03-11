#ifndef __tcp_svr_cli_h__
#define __tcp_svr_cli_h__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include "debug.h"
int tcp_svr_cli_main(int argc, char **argv); 
#include "tcp_test_svr_cli.h"
#include "tcp_svr_cli_socket_prepare.h"
#include "tcp_svr_cli_usage.h"
#endif /*__tcp_svr_cli_h__*/
