// Ethernet communication
#ifndef __UDP_SERVER_COMMUNICATION__
#define __UDP_SERVER_COMMUNICATION__

#define UDP_PACKET_MAX_SIZE 950

#ifndef uint8_t
typedef unsigned char uint8_t;
#endif

typedef struct _upduploadmsg{
	uint8_t version;   // Protocol version
	uint8_t sync_code[2];   // sync code for synchronize request and response  
	uint8_t concentrator_sn[12];
	uint8_t trapper_sn[12];
	uint8_t message;  // 8 bit information, represent for 8 different events
	uint8_t checksum;
} UDP_Upload_Msg_Type;

typedef struct _udpresponcemsg{
	uint8_t version;
	uint8_t sync_code[2];
	uint8_t flag; // success or not
	uint8_t command; // future control feature, keep it 0x00 on this version;
	uint8_t checksum;
} UDP_Responce_Msg_Type;

typedef struct _udpbuffer{
	unsigned int len;
	char data[UDP_PACKET_MAX_SIZE+1];
} UDP_Buffer;

typedef void (*UDP_Receive_Callback)(char*, int);

#define UDP_PACKET_MAX_SIZE	sizeof(UDP_Responce_Msg_Type)


int UDP_init(unsigned char *mac_addr, unsigned int local_port, unsigned char *server_ip, unsigned int server_port, UDP_Receive_Callback cb);
void UDP_sendMsg(UDP_Upload_Msg_Type *packet);
int UDP_ready();
//void receiveUdpMsgCallback(char *data,int len);
int UDP_sendData(UDP_Buffer *buf);
#endif
