#ifndef __SEC_DATA_H__
#define __SEC_DATA_H__

#include "net/uip.h"
//#if ENABLE_CBC_LINK_SECURITY
#define MAX_DEVICES 			5
/* reserved slots in the devices array - to move to C-implementation along the array after work !!!!!!!!!!!!!!!!!!*/
#define EDGE_ROUTER_INDEX		0
#define RESERVED_INDEX			1
/* end of reserved slots */

#define DEVICE_ID_SIZE			16

typedef enum {
	/**< The session key is still valid and fresh */
	FRESH 			= 0x03,
	/**< The session key has expired */
	EXPIRED 		= 0x01,
	/**< The nonce has to be updated in flash */
	UPDATE_NONCE	= 0x02,
	/**< Free spot in device list */
	FREE_SPOT		= 0x00,
	/**< Reserved spot in device list */
	RESERVED		= 0x04,
	/**< Key exchange failed before */
	FAILED			= 0x05,
} keyfreshness_flags_type_t;


/* Global variable for security devices */
struct device_sec_data {
  uip_ipaddr_t  	remote_device_id;
  uint16_t			msg_cntr;
  uint8_t			nonce_cntr;
  uint16_t 			remote_msg_cntr;
  uint8_t 	 		remote_nonce_cntr;
  uint8_t			key_freshness;
  uint8_t			session_key[16];
  unsigned long		time_last_activity;
};

void resetDeviceID_by_Index(uint8_t index);
void reset_sec_data(uint8_t index);
void update_nonce(uint8_t index);
void copy_id_to_reserved(uint8_t index);
void reset_failed_key_exchanges(void);
/*---- UTILS -----------------*/
void set16(uint8_t *buffer, int pos, uint16_t value);
uint16_t get16(uint8_t *buffer, int pos);

extern  struct device_sec_data __attribute__((__d20__)) devices[MAX_DEVICES];

#endif
