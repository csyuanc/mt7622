/* SPDX-License-Identifier: ISC */
/* Copyright (C) 2019 MediaTek Inc. */

#ifndef __MT7622_REGS_H
#define __MT7622_REGS_H

#define MT_HW_REV			0x1000
#define MT_HW_CHIPID			0x1008

#define MT_TOP_OFF_RSV		0x1128
#define MT_TOP_OFF_RSV_FW_STATE		GENMASK(18, 16)

#define MT_HIF_BASE			0x4000
#define MT_HIF(ofs)			(MT_HIF_BASE + (ofs))

#define MT_CFG_LPCR_HOST		MT_HIF(0x1f0)
#define MT_CFG_LPCR_HOST_FW_OWN		BIT(0)
#define MT_CFG_LPCR_HOST_DRV_OWN	BIT(1)

#define MT_INT_SOURCE_CSR		MT_HIF(0x200)
#define MT_INT_MASK_CSR			MT_HIF(0x204)
#define MT_DELAY_INT_CFG		MT_HIF(0x210)

#define MT_INT_RX_DONE(_n)		BIT(_n)
#define MT_INT_RX_DONE_ALL		GENMASK(1, 0)
#define MT_INT_TX_DONE_ALL		GENMASK(19, 4)
#define MT_INT_TX_DONE(_n)		BIT((_n) + 4)

#define MT_WPDMA_GLO_CFG		MT_HIF(0x208)
#define MT_WPDMA_GLO_CFG_TX_DMA_EN	BIT(0)
#define MT_WPDMA_GLO_CFG_TX_DMA_BUSY	BIT(1)
#define MT_WPDMA_GLO_CFG_RX_DMA_EN	BIT(2)
#define MT_WPDMA_GLO_CFG_RX_DMA_BUSY	BIT(3)
#define MT_WPDMA_GLO_CFG_DMA_BURST_SIZE	GENMASK(5, 4)
#define MT_WPDMA_GLO_CFG_TX_WRITEBACK_DONE	BIT(6)
#define MT_WPDMA_GLO_CFG_BIG_ENDIAN	BIT(7)
#define MT_WPDMA_GLO_CFG_FW_RING_BP_TX_SCH	BIT(9)
#define MT_WPDMA_GLO_CFG_MULTI_DMA_EN	GENMASK(11, 10)
#define MT_WPDMA_GLO_CFG_FIFO_LITTLE_ENDIAN	BIT(12)
#define MT_WPDMA_GLO_CFG_TX_BT_SIZE_BIT21	GENMASK(23, 22)
#define MT_WPDMA_GLO_CFG_SW_RESET	BIT(24)
#define MT_WPDMA_GLO_CFG_FIRST_TOKEN_ONLY	BIT(26)
#define MT_WPDMA_GLO_CFG_OMIT_TX_INFO	BIT(28)

#define MT_WPDMA_RST_IDX		MT_HIF(0x20c)

#define MT_TX_RING_BASE			MT_HIF(0x300)
#define MT_RX_RING_BASE			MT_HIF(0x400)

#define MT_WPDMA_GLO_CFG1		MT_HIF(0x500)
#define MT_WPDMA_TX_PRE_CFG		MT_HIF(0x510)
#define MT_WPDMA_RX_PRE_CFG		MT_HIF(0x520)
#define MT_WPDMA_ABT_CFG		MT_HIF(0x530)
#define MT_WPDMA_ABT_CFG1		MT_HIF(0x534)

#define MT_PLE_BASE			0x8000
#define MT_PLE(ofs)			(MT_PLE_BASE + (ofs))

#define MT_PLE_FL_Q0_CTRL		MT_PLE(0x1b0)
#define MT_PLE_FL_Q1_CTRL		MT_PLE(0x1b4)
#define MT_PLE_FL_Q2_CTRL		MT_PLE(0x1b8)
#define MT_PLE_FL_Q3_CTRL		MT_PLE(0x1bc)

#define MT_PLE_AC_QEMPTY(ac, n)		MT_PLE(0x300 + 0x10 * (ac) + \
					       ((n) << 2))

#define MT_WF_PHY_BASE			0x10000
#define MT_WF_PHY(ofs)			(MT_WF_PHY_BASE + (ofs))

#define MT_WF_PHY_WF2_RFCTRL0		MT_WF_PHY(0x1900)
#define MT_WF_PHY_WF2_RFCTRL0_LPBCN_EN	BIT(9)

#define MT_WF_PHY_R0_B0_PHYMUX_5	MT_WF_PHY(0x0614)

#define MT_WF_PHY_R0_B0_PHYCTRL_STS0	MT_WF_PHY(0x020c)
#define MT_WF_PHYCTRL_STAT_PD_OFDM	GENMASK(31, 16)
#define MT_WF_PHYCTRL_STAT_PD_CCK	GENMASK(15, 0)

#define MT_WF_PHY_R0_B0_PHYCTRL_STS5	MT_WF_PHY(0x0220)
#define MT_WF_PHYCTRL_STAT_MDRDY_OFDM	GENMASK(31, 16)
#define MT_WF_PHYCTRL_STAT_MDRDY_CCK	GENMASK(15, 0)

#define MT_WF_PHY_B0_MIN_PRI_PWR	MT_WF_PHY(0x229c)
#define MT_WF_PHY_B0_PD_OFDM_MASK	GENMASK(28, 20)
#define MT_WF_PHY_B0_PD_OFDM(v)		((v) << 20)
#define MT_WF_PHY_B0_PD_BLK		BIT(19)

#define MT_WF_PHY_B1_MIN_PRI_PWR	MT_WF_PHY(0x084)
#define MT_WF_PHY_B1_PD_OFDM_MASK	GENMASK(24, 16)
#define MT_WF_PHY_B1_PD_OFDM(v)		((v) << 16)
#define MT_WF_PHY_B1_PD_BLK		BIT(25)

#define MT_WF_PHY_B0_RXTD_CCK_PD	MT_WF_PHY(0x2310)
#define MT_WF_PHY_B0_PD_CCK_MASK	GENMASK(8, 1)
#define MT_WF_PHY_B0_PD_CCK(v)		((v) << 1)

#define MT_WF_PHY_B1_RXTD_CCK_PD	MT_WF_PHY(0x2314)
#define MT_WF_PHY_B1_PD_CCK_MASK	GENMASK(31, 24)
#define MT_WF_PHY_B1_PD_CCK(v)		((v) << 24)

#define MT_WF_CFG_BASE			0x20200
#define MT_WF_CFG(ofs)			(MT_WF_CFG_BASE + (ofs))

#define MT_CFG_CCR			MT_WF_CFG(0x000)
#define MT_CFG_CCR_MAC_D1_1X_GC_EN	BIT(24)
#define MT_CFG_CCR_MAC_D0_1X_GC_EN	BIT(25)
#define MT_CFG_CCR_MAC_D1_2X_GC_EN	BIT(30)
#define MT_CFG_CCR_MAC_D0_2X_GC_EN	BIT(31)

#define MT_WF_AGG_BASE			0x20a00
#define MT_WF_AGG(ofs)			(MT_WF_AGG_BASE + (ofs))

#define MT_AGG_ARCR			MT_WF_AGG(0x010)
#define MT_AGG_ARCR_INIT_RATE1		BIT(0)
#define MT_AGG_ARCR_RTS_RATE_THR	GENMASK(12, 8)
#define MT_AGG_ARCR_RATE_DOWN_RATIO	GENMASK(17, 16)
#define MT_AGG_ARCR_RATE_DOWN_RATIO_EN	BIT(19)
#define MT_AGG_ARCR_RATE_UP_EXTRA_TH	GENMASK(22, 20)

#define MT_AGG_ARUCR			MT_WF_AGG(0x018)
#define MT_AGG_ARDCR			MT_WF_AGG(0x01c)
#define MT_AGG_ARxCR_LIMIT_SHIFT(_n)	(4 * (_n))
#define MT_AGG_ARxCR_LIMIT(_n)		GENMASK(2 + \
					MT_AGG_ARxCR_LIMIT_SHIFT(_n), \
					MT_AGG_ARxCR_LIMIT_SHIFT(_n))

#define MT_AGG_ASRCR0			MT_WF_AGG(0x060)
#define MT_AGG_ASRCR1			MT_WF_AGG(0x064)
#define MT_AGG_ASRCR_RANGE(val, n)	(((val) >> ((n) << 3)) & GENMASK(5, 0))

#define MT_AGG_ACR0			MT_WF_AGG(0x070)
#define MT_AGG_ACR1			MT_WF_AGG(0x170)
#define MT_AGG_ACR_NO_BA_RULE		BIT(0)
#define MT_AGG_ACR_NO_BA_AR_RULE	BIT(1)
#define MT_AGG_ACR_PKT_TIME_EN		BIT(2)
#define MT_AGG_ACR_CFEND_RATE		GENMASK(15, 4)
#define MT_AGG_ACR_LDPC_UR_EN		BIT(16)
#define MT_AGG_ACR_BAR_RATE		GENMASK(31, 20)

#define MT_AGG_SCR			MT_WF_AGG(0x0fc)
#define MT_AGG_SCR_NLNAV_MID_PTEC_DIS	BIT(3)

#define MT_WF_TMAC_BASE			0x21000
#define MT_WF_TMAC(ofs)			(MT_WF_TMAC_BASE + (ofs))

#define MT_TMAC_TRCR0			MT_WF_TMAC(0x09c)
#define MT_TMAC_TRCR1			MT_WF_TMAC(0x070)
#define MT_TMAC_TRCR_CCA_SEL		GENMASK(31, 30)
#define MT_TMAC_TRCR_SEC_CCA_SEL	GENMASK(29, 28)

#define MT_TMAC_CTCR0			MT_WF_TMAC(0x0f4)
#define MT_TMAC_CTCR0_INS_DDLMT_REFTIME	GENMASK(5, 0)
#define MT_TMAC_CTCR0_INS_DDLMT_DENSITY	GENMASK(15, 12)
#define MT_TMAC_CTCR0_INS_DDLMT_EN	BIT(17)
#define MT_TMAC_CTCR0_INS_DDLMT_VHT_SMPDU_EN	BIT(18)

#define MT_WF_RMAC_BASE			0x21200
#define MT_WF_RMAC(ofs)			(MT_WF_RMAC_BASE + (ofs))

#define MT_WF_RFCR			MT_WF_RMAC(0x000)
#define MT_WF_RFCR_DROP_STBC_MULTI	BIT(0)
#define MT_WF_RFCR_DROP_FCSFAIL		BIT(1)
#define MT_WF_RFCR_DROP_VERSION		BIT(3)
#define MT_WF_RFCR_DROP_PROBEREQ	BIT(4)
#define MT_WF_RFCR_DROP_MCAST		BIT(5)
#define MT_WF_RFCR_DROP_BCAST		BIT(6)
#define MT_WF_RFCR_DROP_MCAST_FILTERED	BIT(7)
#define MT_WF_RFCR_DROP_A3_MAC		BIT(8)
#define MT_WF_RFCR_DROP_A3_BSSID	BIT(9)
#define MT_WF_RFCR_DROP_A2_BSSID	BIT(10)
#define MT_WF_RFCR_DROP_OTHER_BEACON	BIT(11)
#define MT_WF_RFCR_DROP_FRAME_REPORT	BIT(12)
#define MT_WF_RFCR_DROP_CTL_RSV		BIT(13)
#define MT_WF_RFCR_DROP_CTS		BIT(14)
#define MT_WF_RFCR_DROP_RTS		BIT(15)
#define MT_WF_RFCR_DROP_DUPLICATE	BIT(16)
#define MT_WF_RFCR_DROP_OTHER_BSS	BIT(17)
#define MT_WF_RFCR_DROP_OTHER_UC	BIT(18)
#define MT_WF_RFCR_DROP_OTHER_TIM	BIT(19)
#define MT_WF_RFCR_DROP_NDPA		BIT(20)
#define MT_WF_RFCR_DROP_UNWANTED_CTL	BIT(21)

#define MT_WF_RFCR1			MT_WF_RMAC(0x004)
#define MT_WF_RFCR1_DROP_ACK		BIT(4)
#define MT_WF_RFCR1_DROP_BF_POLL	BIT(5)
#define MT_WF_RFCR1_DROP_BA		BIT(6)
#define MT_WF_RFCR1_DROP_CFEND		BIT(7)
#define MT_WF_RFCR1_DROP_CFACK		BIT(8)

#define MT_WF_RMAC_MIB_TIME0		MT_WF_RMAC(0x03c4)
#define MT_WF_RMAC_MIB_RXTIME_CLR	BIT(31)
#define MT_WF_RMAC_MIB_RXTIME_EN	BIT(30)

#define MT_WF_RMAC_MIB_AIRTIME0		MT_WF_RMAC(0x0380)

#define MT_WF_RMAC_MIB_TIME5		MT_WF_RMAC(0x03d8)
#define MT_MIB_OBSSTIME_MASK		GENMASK(23, 0)

#define MT_WF_DMA_BASE			0x21800
#define MT_WF_DMA(ofs)			(MT_WF_DMA_BASE + (ofs))

#define MT_DMA_DCR0			MT_WF_DMA(0x000)
#define MT_DMA_DCR0_MAX_RX_LEN		GENMASK(15, 2)
#define MT_DMA_DCR0_RX_VEC_DROP		BIT(17)

#define MT_DMA_BN0RCFR0			MT_WF_DMA(0x070)
#define MT_DMA_BN1RCFR0			MT_WF_DMA(0x0b0)
#define MT_DMA_RCFR0_MCU_RX_MGMT	BIT(2)
#define MT_DMA_RCFR0_MCU_RX_CTL_NON_BAR	BIT(3)
#define MT_DMA_RCFR0_MCU_RX_CTL_BAR	BIT(4)
#define MT_DMA_RCFR0_MCU_RX_BYPASS	BIT(21)
#define MT_DMA_RCFR0_RX_DROPPED_UCAST	GENMASK(25, 24)
#define MT_DMA_RCFR0_RX_DROPPED_MCAST	GENMASK(27, 26)

#define MT_DMASHDL_BASE			0x5000a000
#define MT_DMASHDL_REMAP		0x2504
#define MT_DMASHDL_OFS(ofs)		(0x80000 + (ofs & 0xffff))

#define MT_DMASHDL(ofs)		(MT_DMASHDL_BASE + (ofs))
#define MT_DMASHDL_OPTION_CTRL	MT_DMASHDL(0x08)
#define MT_DMASHDL_REFILL_CTRL	MT_DMASHDL(0x10)
#define MT_DMASHDL_GROUP0_CTRL	MT_DMASHDL(0x20)
#define MT_DMASHDL_GROUP1_CTRL	MT_DMASHDL(0x24)
#define MT_DMASHDL_GROUP2_CTRL	MT_DMASHDL(0x28)
#define MT_DMASHDL_GROUP3_CTRL	MT_DMASHDL(0x2c)
#define MT_DMASHDL_GROUP4_CTRL	MT_DMASHDL(0x30)
#define MT_DMASHDL_GROUP5_CTRL	MT_DMASHDL(0x34)
#define MT_DMASHDL_GROUP6_CTRL	MT_DMASHDL(0x38)
#define MT_DMASHDL_GROUP7_CTRL	MT_DMASHDL(0x3c)
#define MT_DMASHDL_GROUP8_CTRL	MT_DMASHDL(0x40)
#define MT_DMASHDL_GROUP9_CTRL	MT_DMASHDL(0x44)
#define MT_DMASHDL_GROUP10_CTRL	MT_DMASHDL(0x48)
#define MT_DMASHDL_GROUP11_CTRL	MT_DMASHDL(0x4c)
#define MT_DMASHDL_GROUP12_CTRL	MT_DMASHDL(0x50)
#define MT_DMASHDL_GROUP13_CTRL	MT_DMASHDL(0x54)
#define MT_DMASHDL_GROUP14_CTRL	MT_DMASHDL(0x58)
#define MT_DMASHDL_GROUP15_CTRL	MT_DMASHDL(0x5c)

#define MT_DMASHDL_SET0		MT_DMASHDL(0xb0)
#define MT_DMASHDL_SET1		MT_DMASHDL(0xb4)

#define MT_DMASHDL_Q_MAP0	MT_DMASHDL(0xd0)
#define MT_DMASHDL_Q_MAP1	MT_DMASHDL(0xd4)
#define MT_DMASHDL_Q_MAP2	MT_DMASHDL(0xd8)
#define MT_DMASHDL_Q_MAP3	MT_DMASHDL(0xdc)

#define MT_DMASHDL_PKT_MAX_SIZE MT_DMASHDL(0x1c)

#define DMASHDL_MIN_QUOTA		GENMASK(11, 0)
#define DMASHDL_MAX_QUOTA		GENMASK(27, 16)

#define PLE_PKT_MAX_SIZE		GENMASK(11, 0)
#define PSE_PKT_MAX_SIZE		GENMASK(27, 16)

#define MT_WTBL_BASE			0x30000
#define MT_WTBL_ENTRY_SIZE		256

#define MT_WTBL_OFF_BASE		0x23400
#define MT_WTBL_OFF(n)			(MT_WTBL_OFF_BASE + (n))

#define MT_WTBL_W0_KEY_IDX		GENMASK(24, 23)
#define MT_WTBL_W0_RX_KEY_VALID		BIT(26)
#define MT_WTBL_W0_RX_IK_VALID		BIT(27)

#define MT_WTBL_W2_KEY_TYPE		GENMASK(7, 4)

#define MT_WTBL_UPDATE			MT_WTBL_OFF(0x030)
#define MT_WTBL_UPDATE_WLAN_IDX		GENMASK(7, 0)
#define MT_WTBL_UPDATE_RXINFO_UPDATE	BIT(11)
#define MT_WTBL_UPDATE_ADM_COUNT_CLEAR	BIT(12)
#define MT_WTBL_UPDATE_RATE_UPDATE	BIT(13)
#define MT_WTBL_UPDATE_TX_COUNT_CLEAR	BIT(14)
#define MT_WTBL_UPDATE_BUSY		BIT(31)

#define MT_WTBL_ON_BASE			0x23000
#define MT_WTBL_ON(_n)			(MT_WTBL_ON_BASE + (_n))

#define MT_WTBL_RICR0			MT_WTBL_ON(0x010)
#define MT_WTBL_RICR1			MT_WTBL_ON(0x014)

#define MT_WTBL_RIUCR0			MT_WTBL_ON(0x020)

#define MT_WTBL_RIUCR1			MT_WTBL_ON(0x024)
#define MT_WTBL_RIUCR1_RATE0		GENMASK(11, 0)
#define MT_WTBL_RIUCR1_RATE1		GENMASK(23, 12)
#define MT_WTBL_RIUCR1_RATE2_LO		GENMASK(31, 24)

#define MT_WTBL_RIUCR2			MT_WTBL_ON(0x028)
#define MT_WTBL_RIUCR2_RATE2_HI		GENMASK(3, 0)
#define MT_WTBL_RIUCR2_RATE3		GENMASK(15, 4)
#define MT_WTBL_RIUCR2_RATE4		GENMASK(27, 16)
#define MT_WTBL_RIUCR2_RATE5_LO		GENMASK(31, 28)

#define MT_WTBL_RIUCR3			MT_WTBL_ON(0x02c)
#define MT_WTBL_RIUCR3_RATE5_HI		GENMASK(7, 0)
#define MT_WTBL_RIUCR3_RATE6		GENMASK(19, 8)
#define MT_WTBL_RIUCR3_RATE7		GENMASK(31, 20)

#define MT_WTBL_W5_CHANGE_BW_RATE	GENMASK(7, 5)
#define MT_WTBL_W5_SHORT_GI_20		BIT(8)
#define MT_WTBL_W5_SHORT_GI_40		BIT(9)
#define MT_WTBL_W5_SHORT_GI_80		BIT(10)
#define MT_WTBL_W5_SHORT_GI_160		BIT(11)
#define MT_WTBL_W5_BW_CAP		GENMASK(13, 12)
#define MT_WTBL_W5_MPDU_FAIL_COUNT	GENMASK(25, 23)
#define MT_WTBL_W5_MPDU_OK_COUNT	GENMASK(28, 26)
#define MT_WTBL_W5_RATE_IDX		GENMASK(31, 29)

#define MT_WTBL_W27_CC_BW_SEL		GENMASK(6, 5)

#define MT_LPON_BASE			0x24200
#define MT_LPON(_n)			(MT_LPON_BASE + (_n))

#define MT_LPON_T0CR			MT_LPON(0x010)
#define MT_LPON_T0CR_MODE		GENMASK(1, 0)

#define MT_LPON_UTTR0			MT_LPON(0x018)
#define MT_LPON_UTTR1			MT_LPON(0x01c)

#define MT_WF_MIB_BASE			0x24800
#define MT_WF_MIB(ofs)			(MT_WF_MIB_BASE + (ofs))

#define MT_MIB_M0_MISC_CR		MT_WF_MIB(0x00c)
#define MT_MIB_MB_SDR0(n)		MT_WF_MIB(0x100 + ((n) << 4))
#define MT_MIB_RTS_RETRIES_COUNT_MASK	GENMASK(31, 16)
#define MT_MIB_RTS_COUNT_MASK		GENMASK(15, 0)

#define MT_MIB_SDR9(n)			MT_WF_MIB(0x02c + ((n) << 9))
#define MT_MIB_SDR9_BUSY_MASK		GENMASK(23, 0)

#define MT_MIB_SDR16(n)			MT_WF_MIB(0x048 + ((n) << 9))
#define MT_MIB_SDR16_BUSY_MASK		GENMASK(23, 0)

#define MT_MIB_SDR36(n)			MT_WF_MIB(0x098 + ((n) << 9))
#define MT_MIB_SDR36_TXTIME_MASK	GENMASK(23, 0)
#define MT_MIB_SDR37(n)			MT_WF_MIB(0x09c + ((n) << 9))
#define MT_MIB_SDR37_RXTIME_MASK	GENMASK(23, 0)

#define MT_TX_AGG_CNT(n)		MT_WF_MIB(0xa8 + ((n) << 2))

#endif
