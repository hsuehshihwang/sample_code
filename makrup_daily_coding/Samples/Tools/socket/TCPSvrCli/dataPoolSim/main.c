#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#define __file__ strrchr(__FILE__, '/')?strrchr(__FILE__, '/')+1:__FILE__
#define dbg(fmt, ...) do{\
	fprintf(stdout, "%s(%d)@%s: " fmt "\n", __FUNCTION__, __LINE__, __file__, ## __VA_ARGS__); \
	fflush(stdout); \
}while(0); 
#define dbge(fmt, ...) do{\
	fprintf(stderr, "%s(%d)@%s: " fmt "\n", __FUNCTION__, __LINE__, __file__, ## __VA_ARGS__); \
	fflush(stdout); \
}while(0); 

#define REPEAT_5(C) C C C C C
#define REPEAT_10(C) REPEAT_5(C) REPEAT_5(C)
#define REPEAT_20(C) REPEAT_10(C) REPEAT_10(C)
#define REPEAT_40(C) REPEAT_20(C) REPEAT_20(C)
#define REPEAT_80(C) REPEAT_40(C) REPEAT_40(C)

#define REPEAT(C,n) REPEAT_##n(C)

#define FUNC_BAR REPEAT("=",20)

#define FUNC_TITLE \
    do { \
        printf("%.*s %s %.*s\n", (int)(strlen(FUNC_BAR)-strlen(__FUNCTION__)/2), FUNC_BAR, __FUNCTION__, (int)(strlen(FUNC_BAR)-strlen(__FUNCTION__)/2-strlen(__FUNCTION__)%2), FUNC_BAR); \
		fflush(stdout); \
    } while(0); 


#define MAXPOOLSIZE 128

typedef struct circularBuffer {
	uint8_t buf[MAXPOOLSIZE]; 
	int r_pos;
	int w_pos;
	int size; 
} circularBuffer; 

void cb_init(circularBuffer *cb){
	if(cb){
		cb->r_pos=0; 
		cb->w_pos=0; 
		cb->size=0; 
	}
}

void cb_config(circularBuffer *cb, int r_pos, int w_pos, int size){
	if(cb){
		cb->r_pos=r_pos; 
		cb->w_pos=w_pos; 
		cb->size=size; 
	}
}

uint8_t *cb_read(circularBuffer *cb, int *size, char *delim){
	uint8_t *data=NULL; 
	if(cb){
		int space_at_end=MAXPOOLSIZE-cb->r_pos; 
		if(delim){
			int delim_len=strlen(delim); 
			int delim_hunt=0; 
			int delim_pos=cb->r_pos; 
			int r_pos=cb->r_pos; 
			int total=cb->size-delim_len; 
			// dbge("total(%d) r_pos(%d) delim_pos(%d)", total, r_pos, delim_pos); 
			while(total){
				// dbge("\ttotal(%d) r_pos(%d) delim_pos(%d)", total, r_pos, delim_pos); 
				for(int i=0; i<delim_len; i++){
					// dbge("\t\tbuf[%d]: %c, delim[%d]: %c", delim_pos, cb->buf[delim_pos], i, delim[i]); 
					if(cb->buf[delim_pos]==delim[i]){
						delim_hunt=1; 
					}else{
						delim_hunt=0; 
						break; 
					}
					if(delim_hunt) break; 
					delim_pos++; 
					if(delim_pos==MAXPOOLSIZE) delim_pos=0; 
				}
				if(delim_hunt) break; 
				r_pos++; 
				total--; 
				if(r_pos==MAXPOOLSIZE) r_pos=0; 
				delim_pos=r_pos; 
			}
			if(delim_hunt){
				dbge("delim_hunt, delim_pos: %d", delim_pos); 
				*size=0; 
				if(delim_pos<cb->r_pos){
					*size=MAXPOOLSIZE-cb->r_pos+delim_pos; 
					data=malloc(*size); 
					memcpy(data, cb->buf+cb->r_pos, MAXPOOLSIZE-cb->r_pos); 
					memcpy(data+MAXPOOLSIZE-cb->r_pos, cb->buf, delim_pos); 
				}else if(delim_pos>cb->r_pos){
					*size=delim_pos-cb->r_pos; 
					data=malloc(*size); 
					memcpy(data, cb->buf+cb->r_pos, *size); 
				}
				cb->r_pos=delim_pos; 
				cb->r_pos+=delim_len; 
				cb->r_pos%=MAXPOOLSIZE; 
				cb->size-=(*size); 
			}
		}else{
			data=malloc(cb->size); 
			if(data){
				if(space_at_end<cb->size){
					memcpy(data, cb->buf+cb->r_pos, space_at_end); 
					memcpy(data+space_at_end, cb->buf, cb->size-space_at_end); 
				}else{
					memcpy(data, cb->buf+cb->r_pos, cb->size); 
				}
				*size=cb->size; 
				cb->size=0; 
				cb->r_pos=0; 
				cb->w_pos=0; 
			}
		}
	}
	return data; 
}

void cb_write(circularBuffer *cb, uint8_t *data, int size){
	if(cb&&data&&size>0){
		if(size>(MAXPOOLSIZE-cb->size)){
			dbge("over the rest!!"); 
			return; 
		}
	}
	int space_at_end=MAXPOOLSIZE-cb->w_pos; 
	if(space_at_end<size){
		memcpy(cb->buf+cb->w_pos, data, space_at_end); 
		memcpy(cb->buf, data+space_at_end, size-space_at_end); 
		cb->w_pos=size-space_at_end; 
	}else{
		memcpy(cb->buf+cb->w_pos, data, size); 
		cb->w_pos+=size; 
	}
	cb->size+=size; 
}

void testcase001(void){
	circularBuffer cb; 
	cb_init(&cb); 
	{
		uint8_t buf[]="Hellow World!!"; 
		cb_write(&cb, (uint8_t *)buf, sizeof(buf)-1); 
	}
	{
		uint8_t buf[]="I'm Ralph!!"; 
		cb_write(&cb, (uint8_t *)buf, sizeof(buf)-1); 
	}
	{
		int size=0; 
		uint8_t *data=cb_read(&cb, &size, NULL); 
		printf("data[%d]: ", size); 
		for(int i=0; i<size; i++){
			printf("%c", data[i]); 
		}
		printf("\n"); 
		printf("data_hex[%d]: ", size); 
		for(int i=0; i<size; i++){
			printf("%02X ", data[i]); 
		}
		printf("\n"); 
	}
}

void testcase002(void){
	circularBuffer cb; 
	cb_init(&cb); 
	{
		uint8_t buf[]="Hellow World!!\r\n"; 
		cb_write(&cb, (uint8_t *)buf, sizeof(buf)-1); 
	}
	{
		uint8_t buf[]="I'm Ralph!!\r\n"; 
		cb_write(&cb, (uint8_t *)buf, sizeof(buf)-1); 
	}
	{
		int size=0; 
		uint8_t *data=cb_read(&cb, &size, NULL); 
		printf("data[%d]: ", size); 
		for(int i=0; i<size; i++){
			printf("%c", data[i]); 
		}
		printf("\n"); 
		printf("data_hex[%d]: ", size); 
		for(int i=0; i<size; i++){
			printf("%02X ", data[i]); 
		}
		printf("\n"); 
	}
}

void testcase003(void){
	circularBuffer cb; 
	cb_init(&cb); 
	cb_config(&cb, 113, 113, 0); 
	{
		uint8_t buf[]="Hellow World!!\r\n"; 
		cb_write(&cb, (uint8_t *)buf, sizeof(buf)-1); 
	}
	{
		uint8_t buf[]="I'm Ralph!!\r\n"; 
		cb_write(&cb, (uint8_t *)buf, sizeof(buf)-1); 
	}
	{
		int size=0; 
		uint8_t *data=cb_read(&cb, &size, (char *)"\r\n"); 
		printf("data[%d]: ", size); 
		for(int i=0; i<size; i++){
			printf("%c", data[i]); 
		}
		printf("\n"); 
		printf("data_hex[%d]: ", size); 
		for(int i=0; i<size; i++){
			printf("%02X ", data[i]); 
		}
		printf("\n"); 
	}
	{
		int size=0; 
		uint8_t *data=cb_read(&cb, &size, (char *)"\r\n"); 
		printf("data[%d]: ", size); 
		for(int i=0; i<size; i++){
			printf("%c", data[i]); 
		}
		printf("\n"); 
		printf("data_hex[%d]: ", size); 
		for(int i=0; i<size; i++){
			printf("%02X ", data[i]); 
		}
		printf("\n"); 
	}
}

int main(int argc, char *argv[]){
	dbge(); 
	{
		// testcase001(); 
		// testcase002(); 
		testcase003(); 
	}
    exit(EXIT_SUCCESS);
}

