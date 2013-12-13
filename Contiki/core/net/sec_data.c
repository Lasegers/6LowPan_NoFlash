#include "net/sec_data.h"
#include <string.h>

//struct device_sec_data __attribute__((__d20__)) devices[MAX_DEVICES];

void resetDeviceID_by_Index(uint8_t index)
{
	memset(&devices[index].remote_device_id.u8[0], 0, DEVICE_ID_SIZE);
}

/*-----------------------------------------------------------------------------------*/
/**
 *	Reset security data from device at position "index"
 *
 *	@param current device_index															NIET AF!
 */
/*-----------------------------------------------------------------------------------*/
void reset_sec_data(uint8_t index)
{
	devices[index].nonce_cntr = 1;
	devices[index].msg_cntr = 0;
	devices[index].remote_msg_cntr = 0;
	devices[index].remote_nonce_cntr = 0;
	devices[index].time_last_activity = 0;

	if(index != RESERVED_INDEX) {
		/* Set as free spot */
		devices[index].key_freshness = FREE_SPOT;
		/* Reset device id */
		//memset(&devices[index].remote_device_id.u8[0], 0, DEVICE_ID_SIZE);
		resetDeviceID_by_Index(index);
	}
}
/*-----------------------------------------------------------------------------------*/
/**
 * Update nonce writes the new nonce of devices[index] to flash memory
 *
 * @param index of device																NIET GETEST!
 */
/*-----------------------------------------------------------------------------------*/
void update_nonce(uint8_t index)
{
	devices[index].key_freshness = FRESH;
}
/**
 *	Copy the device id to the reserved spot for key-exchange
 *
 *	@param current device_index															NIET AF!
 */
/*-----------------------------------------------------------------------------------*/
void copy_id_to_reserved(uint8_t index)
{
	memcpy(&devices[RESERVED_INDEX].remote_device_id.u8[0], &devices[index].remote_device_id.u8[0], DEVICE_ID_SIZE);
}

/*-----------------------------------------------------------------------------------*/
/**
 *	Reset the failed key-exchanges to expired											NIET AF!
 */
/*-----------------------------------------------------------------------------------*/
void reset_failed_key_exchanges(void)
{
	uint8_t i;
	for(i=2; i<MAX_DEVICES; i++) {
		if(devices[i].key_freshness == FAILED) {
			devices[i].key_freshness = EXPIRED;
		}
	}
}

/*---------------------------------------------------------------------------*/
/*-- CAN BE MOVED TO UTILS --*/
uint16_t get16(uint8_t *buffer, int pos)
{
  return (uint16_t)buffer[pos] << 8 | buffer[pos + 1];
}
/*---------------------------------------------------------------------------*/
void set16(uint8_t *buffer, int pos, uint16_t value)
{
  buffer[pos++] = value >> 8;
  buffer[pos++] = value & 0xff;
}
