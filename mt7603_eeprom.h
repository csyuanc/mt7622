/*
 * Copyright (C) 2015 Felix Fietkau <nbd@openwrt.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __MT7603_EEPROM_H
#define __MT7603_EEPROM_H

#include "mt7603.h"

enum mt7603_eeprom_field {
	MT_EE_CHIP_ID =				0x000,
	MT_EE_VERSION =				0x002,
	MT_EE_MAC_ADDR =			0x004,
	MT_EE_NIC_CONF_0 =			0x034,
	MT_EE_NIC_CONF_1 =			0x036,
	MT_EE_NIC_CONF_2 =			0x042,

	MT_EE_XTAL_TRIM_1 =			0x03a,

	MT_EE_RSSI_OFFSET_2G =			0x046,
	MT_EE_WIFI_RF_SETTING =			0x048,
	MT_EE_RSSI_OFFSET_5G =			0x04a,

	MT_EE_TX_POWER_DELTA_BW40 =		0x050,
	MT_EE_TX_POWER_DELTA_BW80 =		0x052,

	MT_EE_TX_POWER_EXT_PA_5G =		0x054,

	MT_EE_TEMP_SENSOR_CAL =			0x055,

	MT_EE_TX_POWER_0_START_2G =		0x056,
	MT_EE_TX_POWER_1_START_2G =		0x05c,

	/* used as byte arrays */
#define MT_TX_POWER_GROUP_SIZE_5G		5
#define MT_TX_POWER_GROUPS_5G			6
	MT_EE_TX_POWER_0_START_5G =		0x062,

	MT_EE_TX_POWER_0_GRP3_TX_POWER_DELTA =	0x074,
	MT_EE_TX_POWER_0_GRP4_TSSI_SLOPE =	0x076,

	MT_EE_TX_POWER_1_START_5G =		0x080,


	MT_EE_TX_POWER_CCK =			0x0a0,
	MT_EE_TX_POWER_OFDM_2G_6M =		0x0a2,
	MT_EE_TX_POWER_OFDM_2G_24M =		0x0a4,
	MT_EE_TX_POWER_OFDM_2G_54M =		0x0a6,
	MT_EE_TX_POWER_HT_BPSK_QPSK =		0x0a8,
	MT_EE_TX_POWER_HT_16_64_QAM =		0x0aa,
	MT_EE_TX_POWER_HT_64_QAM =		0x0ac,

	MT_EE_ELAN_RX_MODE_GAIN =		0x0c0,
	MT_EE_ELAN_RX_MODE_NF =			0x0c1,
	MT_EE_ELAN_RX_MODE_P1DB =		0x0c2,

	MT_EE_ELAN_BYPASS_MODE_GAIN =		0x0c3,
	MT_EE_ELAN_BYPASS_MODE_NF =		0x0c4,
	MT_EE_ELAN_BYPASS_MODE_P1DB =		0x0c5,

	MT_EE_STEP_NUM_NEG_6_7 =		0x0c6,
	MT_EE_STEP_NUM_NEG_4_5 =		0x0c8,
	MT_EE_STEP_NUM_NEG_2_3 =		0x0ca,
	MT_EE_STEP_NUM_NEG_0_1 =		0x0cc,

	MT_EE_REF_STEP_24G =			0x0ce,

	MT_EE_STEP_NUM_PLUS_1_2 =		0x0d0,
	MT_EE_STEP_NUM_PLUS_3_4 =		0x0d2,
	MT_EE_STEP_NUM_PLUS_5_6 =		0x0d4,
	MT_EE_STEP_NUM_PLUS_7 =			0x0d6,

	MT_EE_XTAL_FREQ_OFFSET =		0x0f4,
	MT_EE_XTAL_TRIM_2_COMP =		0x0f5,
	MT_EE_XTAL_TRIM_3_COMP =		0x0f6,
	MT_EE_XTAL_WF_RFCAL =			0x0f7,

	__MT_EE_MAX
};

enum mt7603_eeprom_source {
	MT_EE_SRC_PROM,
	MT_EE_SRC_EFUSE,
	MT_EE_SRC_FLASH,
};

#endif