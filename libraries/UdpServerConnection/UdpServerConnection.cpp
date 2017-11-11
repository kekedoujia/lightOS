// Ethernet communication
#include "TrapperConfig.h"
#include "UdpServerConnection.h"
#include "Dhcp.h"
#include "Dns.h"
#include "Ethernet2.h"
//include "EthernetClient.h"
#include "EthernetUdp2.h"
#include "lightOS.h"
#include "MyFunction.h"
#include "Arduino.h"


unsigned char _udp_mac[6];
unsigned char _udp_server_ip[4];
unsigned int _udp_server_port;
unsigned int _udp_local_port;
int _udp_ethernet_flag = -1;
//int _udp_wait_responce = 0;
//char _udp_packetBuffer[UDP_PACKET_MAX_SIZE+1];
//unsigned long receiving_waiting = 0;
//UDP_Responce_Msg_Type *recv_packet = (UDP_Responce_Msg_Type *)_udp_packetBuffer;
UDP_Buffer receive_buf;
UDP_Receive_Callback _udp_receive_callback = NULL;
char *_udp_packetBuffer = (char *)(&receive_buf);

OS_TASK *_udp_listen_task;


static EthernetUDP _conn_UDP;
unsigned int _udp_listenningTask(int opt);

int UDP_init(unsigned char *mac_addr, unsigned int local_port, unsigned char *server_ip, unsigned int server_port, UDP_Receive_Callback cb) {
	memcpy(_udp_mac, mac_addr, 6);
	memcpy(_udp_server_ip, server_ip, 4);
	_udp_server_port = server_port;
	_udp_local_port = local_port;
	_udp_listen_task = taskRegister(_udp_listenningTask, OS_ST_PER_10_MS*100, 1, 0);	
	Ethernet.init(10);
	if (Ethernet.begin(_udp_mac)){
		_udp_ethernet_flag = 1;	
		_conn_UDP.begin(_udp_local_port);	
	}
	else {
		_udp_ethernet_flag = -1;
		taskNextDutyDelay(_udp_listen_task,OS_ST_PER_MINUTE*2);
	}
	Serial.println(Ethernet.localIP());
	_udp_receive_callback = cb;
	return _udp_ethernet_flag;
}

int UDP_ready(){
	if (_udp_ethernet_flag == 1) return 1;
	else return 0; 
}

int UDP_sendData(UDP_Buffer *buf){
	if (buf->len > 900 || buf->len<1 || _udp_ethernet_flag== -1) return -1;
	generateChecksumFixZero((uint8_t *)buf,buf->len+sizeof(unsigned int),1);
	IPAddress serv(_udp_server_ip[0],_udp_server_ip[1],_udp_server_ip[2],_udp_server_ip[3]);
	_conn_UDP.beginPacket(serv,_udp_server_port);
	_conn_UDP.write((char *)buf, buf->len+sizeof(unsigned int)+1);
	_conn_UDP.endPacket();
	return 1;
}

unsigned int _udp_listenningTask(int opt){
	unsigned char check;
	unsigned int i;
	int pSize = 0;

	//digitalWrite(RFM95_CS,HIGH);

	if (_udp_ethernet_flag == -1) {
		Serial.println("Ethernet is not ready.");
		if (Ethernet.begin(_udp_mac)){
			_udp_ethernet_flag = 1;	
			_conn_UDP.begin(_udp_local_port);	
		}
		else {
			_udp_ethernet_flag = -1;
			taskNextDutyDelay(_udp_listen_task,OS_ST_PER_MINUTE*5);
			return 0;
		}
		return 0;
	}

	
	pSize = _conn_UDP.parsePacket();

	Serial.print("packet size : ");Serial.println(pSize);
	
	if (pSize>0) {
		memset((char *)(&receive_buf),0,UDP_PACKET_MAX_SIZE);
		_conn_UDP.read(_udp_packetBuffer, sizeof(receive_buf));
		Serial.print("receive data size : ");
		Serial.println(receive_buf.len);
		Serial.println(receive_buf.data);
		receive_buf.data[receive_buf.len] = 0;
		
		_udp_receive_callback(receive_buf.data,receive_buf.len);
		check = 0;
		for (i = 0; i < receive_buf.len; i++) check += _udp_packetBuffer[i];
		if (check != 0x00) {
			_conn_UDP.flush();
			return 0;
		}
		//IPAddress remote = _conn_UDP.remoteIP();
		//IPAddress ser = IPAddress(_udp_server_ip);
		//if (receive_buf.len != (packetSize-3)) return 0;
		//_udp_receive_callback(receive_buf.data,receive_buf.len);
	}
	else{
		_conn_UDP.flush();
	}
	return 1;
}
