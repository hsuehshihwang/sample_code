#ifndef __cmd_h__
#define __cmd_h__
typedef enum {
	CMD_TEST=1, 
	CMD_MSG, 
	CMD_SHELL, 
	CMD_NEW_FILE, 
	CMD_APPEND_FILE, 
	CMD_REMOVE_FILE, 
	CMD_END
} cmd_type; 

typedef struct cmd_type_desc {
	cmd_type type; 
	const char *desc; 
} cmd_type_desc; 

#define CMD_TYPE_DESC(type)  {type, #type}
cmd_type_desc cmd_type_desc_tab[]={
	CMD_TYPE_DESC(CMD_TEST), 
	CMD_TYPE_DESC(CMD_MSG), 
	CMD_TYPE_DESC(CMD_SHELL), 
	CMD_TYPE_DESC(CMD_NEW_FILE), 
	CMD_TYPE_DESC(CMD_APPEND_FILE), 
	CMD_TYPE_DESC(CMD_REMOVE_FILE), 
	CMD_TYPE_DESC(CMD_END)
}; 

const char *get_cmd_type_desc(cmd_type type){
	const char *pdesc="(none)"; 
	for(cmd_type_desc *ptab=cmd_type_desc_tab; ptab->type!=CMD_END;ptab++){
		if(ptab->type==type){
			pdesc=ptab->desc; 
			break; 
		}
	}
	return pdesc; 
}

#define CMD_MAGIC 0x11223344
typedef struct cmd {
	unsigned int magic; 
	unsigned int type; 
	unsigned int length; 
} cmd; 
#endif /* __cmd_h__ */
