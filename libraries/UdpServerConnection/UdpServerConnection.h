#ifndef LIGHTOS_LIBRARIES_UDP_SERVER_CONNECTION_H_
#define LIGHTOS_LIBRARIES_UDP_SERVER_CONNECTION_H_

#define UDP_PACKET_MAX_SIZE 950

#ifndef uint8_t
typedef unsigned char uint8_t;
#endif

typedef struct {
  uint8_t version;
  uint8_t sync_code[2];
  uint8_t concentrator_sn[12];
  uint8_t trapper_sn[12];
  uint8_t message;
  uint8_t checksum;
} UdpUploadMsg;

typedef struct {
  uint8_t version;
  uint8_t sync_code[2];
  uint8_t flag;
  uint8_t command;
  uint8_t checksum;
} UdpResponseMsg;

typedef struct {
  unsigned int len;
  char data[UDP_PACKET_MAX_SIZE + 1];
} UdpBuffer;

typedef void (*UdpReceiveCallback)(char *data, int len);

int udp_init(unsigned char *mac_addr, unsigned int local_port,
             unsigned char *server_ip, unsigned int server_port,
             UdpReceiveCallback callback);
void udp_send_msg(UdpUploadMsg *packet);
int udp_ready(void);
int udp_send_data(UdpBuffer *buffer);

#endif  // LIGHTOS_LIBRARIES_UDP_SERVER_CONNECTION_H_
