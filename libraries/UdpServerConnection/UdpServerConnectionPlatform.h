#ifndef LIGHTOS_LIBRARIES_UDP_SERVER_CONNECTION_PLATFORM_H_
#define LIGHTOS_LIBRARIES_UDP_SERVER_CONNECTION_PLATFORM_H_

#ifdef __cplusplus
extern "C" {
#endif

int udp_platform_init(const unsigned char *mac_addr);
int udp_platform_begin(unsigned int local_port);
int udp_platform_parse_packet(void);
int udp_platform_read(char *buffer, unsigned int len);
void udp_platform_flush(void);
int udp_platform_send(const unsigned char *server_ip, unsigned int server_port,
                      const char *data, unsigned int len);
void udp_platform_log(const char *message);
void udp_platform_log_int(const char *label, int value);

#ifdef __cplusplus
}
#endif

#endif  // LIGHTOS_LIBRARIES_UDP_SERVER_CONNECTION_PLATFORM_H_
