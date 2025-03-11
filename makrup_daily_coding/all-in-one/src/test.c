#include <stdio.h>
int test_main(int argc, char *argv[]){
	printf("%.*stest\n", 10, "     "); 
	printf("%.*stest\n", 5, "                                   "); 
	char swupgrade_str[16]={0}; 
	const char fmt[]="swupdate -v -e orion,tclinux -i /tmp/firmware/imagedwld/%s"; 
	snprintf(swupgrade_str, sizeof(swupgrade_str), fmt, "rtv7906vw-d223-rev2-TCLINUX-SWU-IMAGE.img"); 
	printf("swupgrade_str(%s)\n", swupgrade_str); 
	return 0; 
}
