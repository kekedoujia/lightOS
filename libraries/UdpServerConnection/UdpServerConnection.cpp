#include "UdpServerConnection.h"

#include "UdpServerConnectionPlatform.h"
#include "../../lightOS/lightOS.h"

#include <stddef.h>
#include <string.h>

static unsigned char udp_mac[6];
static unsigned char udp_server_ip[4];
static unsigned int udp_server_port;
static unsigned int udp_local_port;
static int udp_ethernet_flag = -1;
static UdpBuffer receive_buf;
static UdpReceiveCallback udp_receive_callback = NULL;
static char *udp_packet_buffer = (char *)(&receive_buf);
static OsTask *udp_listen_task;

static unsigned int udp_listening_task(int opt);
static void udp_write_checksum(char *data, unsigned int len_without_checksum);

int udp_init(unsigned char *mac_addr, unsigned int local_port,
             unsigned char *server_ip, unsigned int server_port,
             UdpReceiveCallback callback) {
  memcpy(udp_mac, mac_addr, 6);
  memcpy(udp_server_ip, server_ip, 4);
  udp_server_port = server_port;
  udp_local_port = local_port;
  udp_listen_task =
      task_register(udp_listening_task, OS_ST_PER_10_MS * 100, TASK_RUN, 0);

  if (udp_platform_init(udp_mac)) {
    udp_ethernet_flag = 1;
    udp_platform_begin(udp_local_port);
  } else {
    udp_ethernet_flag = -1;
    task_next_duty_delay(udp_listen_task, OS_ST_PER_MINUTE * 2);
  }

  udp_receive_callback = callback;
  return udp_ethernet_flag;
}

int udp_ready(void) { return udp_ethernet_flag == 1 ? 1 : 0; }

int udp_send_data(UdpBuffer *buffer) {
  if (buffer == NULL || buffer->len > UDP_PACKET_MAX_SIZE ||
      buffer->len < 1 || udp_ethernet_flag == -1) {
    return -1;
  }

  udp_write_checksum((char *)buffer, buffer->len + sizeof(unsigned int));
  udp_platform_send(udp_server_ip, udp_server_port, (char *)buffer,
                    buffer->len + sizeof(unsigned int) + 1);
  return 1;
}

void udp_send_msg(UdpUploadMsg *packet) {
  unsigned int i;
  uint8_t checksum = 0;

  if (packet == NULL || udp_ethernet_flag == -1) {
    return;
  }

  packet->checksum = 0;
  for (i = 0; i < sizeof(UdpUploadMsg) - 1; i++) {
    checksum += ((uint8_t *)packet)[i];
  }
  packet->checksum = 0 - checksum;

  udp_platform_send(udp_server_ip, udp_server_port, (char *)packet,
                    sizeof(UdpUploadMsg));
}

static unsigned int udp_listening_task(int opt) {
  unsigned char check;
  unsigned int i;
  int packet_size;
  (void)opt;

  if (udp_ethernet_flag == -1) {
    udp_platform_log("Ethernet is not ready.");
    if (udp_platform_init(udp_mac)) {
      udp_ethernet_flag = 1;
      udp_platform_begin(udp_local_port);
    } else {
      udp_ethernet_flag = -1;
      task_next_duty_delay(udp_listen_task, OS_ST_PER_MINUTE * 5);
      return 0;
    }
    return 0;
  }

  packet_size = udp_platform_parse_packet();
  udp_platform_log_int("packet size : ", packet_size);

  if (packet_size <= 0) {
    udp_platform_flush();
    return 1;
  }

  memset(&receive_buf, 0, sizeof(receive_buf));
  udp_platform_read(udp_packet_buffer, sizeof(receive_buf));
  if (receive_buf.len > UDP_PACKET_MAX_SIZE) {
    udp_platform_flush();
    return 0;
  }

  udp_platform_log_int("receive data size : ", receive_buf.len);
  udp_platform_log(receive_buf.data);
  receive_buf.data[receive_buf.len] = 0;

  check = 0;
  for (i = 0; i < receive_buf.len + sizeof(unsigned int) + 1; i++) {
    check += udp_packet_buffer[i];
  }
  if (check != 0x00) {
    udp_platform_flush();
    return 0;
  }

  if (udp_receive_callback != NULL) {
    udp_receive_callback(receive_buf.data, receive_buf.len);
  }
  return 1;
}

static void udp_write_checksum(char *data, unsigned int len_without_checksum) {
  unsigned int i;
  unsigned char checksum = 0;

  for (i = 0; i < len_without_checksum; i++) {
    checksum += (unsigned char)data[i];
  }
  data[len_without_checksum] = (char)(0 - checksum);
}
