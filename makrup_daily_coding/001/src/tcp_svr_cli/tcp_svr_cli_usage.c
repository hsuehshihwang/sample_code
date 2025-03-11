#include "tcp_svr_cli.h"
const char tcp_svr_cli_usage_str[]="                    \n\
Usage:                                                  \n\
    %s svr                                              \n\
    %s cli <IP>                                         \n\
        IP: ex: 192.168.1.1                             \n\
            ex: 192.168.1.1                             \n\
    %s test svr                                         \n\
    %s test cli <IP>                                    \n\
        IP: ex: 192.168.1.1                             \n\
                                                        \n\
"; 
void tcp_svr_cli_usage(const char *name){
	enter_n_exit(); 
	printf((const char*)tcp_svr_cli_usage_str, 
			name, name, name, name); 
}
