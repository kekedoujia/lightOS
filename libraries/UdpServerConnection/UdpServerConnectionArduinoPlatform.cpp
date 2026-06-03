#include "UdpServerConnectionPlatform.h"

#include "../../lightOS/os_config.h"

#ifdef _Arduino_Platform_Application_
#include "Arduino.h"
#include "Ethernet2.h"
#include "EthernetUdp2.h"

static EthernetUDP udp_connection;

int udp_platform_init(const unsigned char *mac_addr) {
  Ethernet.init(10);
  return Ethernet.begin((uint8_t *)mac_addr) ? 1 : 0;
}

int udp_platform_begin(unsigned int local_port) {
  udp_connection.begin(local_port);
  Serial.println(Ethernet.localIP());
  return 1;
}

int udp_platform_parse_packet(void) { return udp_connection.parsePacket(); }

int udp_platform_read(char *buffer, unsigned int len) {
  return udp_connection.read(buffer, len);
}

void udp_platform_flush(void) { udp_connection.flush(); }

int udp_platform_send(const unsigned char *server_ip, unsigned int server_port,
                      const char *data, unsigned int len) {
  IPAddress server(server_ip[0], server_ip[1], server_ip[2], server_ip[3]);
  udp_connection.beginPacket(server, server_port);
  udp_connection.write(data, len);
  udp_connection.endPacket();
  return 1;
}

void udp_platform_log(const char *message) { Serial.println(message); }

void udp_platform_log_int(const char *label, int value) {
  Serial.print(label);
  Serial.println(value);
}
#endif
