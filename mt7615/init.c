// SPDX-License-Identifier: ISC
/* Copyright (C) 2019 MediaTek Inc.
 *
 * Author: Roy Luo <royluo@google.com>
 *         Ryder Lee <ryder.lee@mediatek.com>
 *         Felix Fietkau <nbd@nbd.name>
 */

#include <linux/etherdevice.h>
#include "mt7615.h"
#include "mac.h"
#include "eeprom.h"

static void mt7615_phy_init(struct mt7615_dev *dev)
{
	/* disable rf low power beacon mode */
	mt76_set(dev, MT_WF_PHY_WF2_RFCTRL0(0), MT_WF_PHY_WF2_RFCTRL0_LPBCN_EN);
	mt76_set(dev, MT_WF_PHY_WF2_RFCTRL0(1), MT_WF_PHY_WF2_RFCTRL0_LPBCN_EN);
}

static void mt7615_mac_init(struct mt7615_dev *dev)
{
	u32 val, mask, set;
	int i;

	/* enable band 0/1 clk */
	mt76_set(dev, MT_CFG_CCR,
		 MT_CFG_CCR_MAC_D0_1X_GC_EN | MT_CFG_CCR_MAC_D0_2X_GC_EN |
		 MT_CFG_CCR_MAC_D1_1X_GC_EN | MT_CFG_CCR_MAC_D1_2X_GC_EN);

	val = mt76_rmw(dev, MT_TMAC_TRCR0,
		       MT_TMAC_TRCR_CCA_SEL | MT_TMAC_TRCR_SEC_CCA_SEL,
		       FIELD_PREP(MT_TMAC_TRCR_CCA_SEL, 2) |
		       FIELD_PREP(MT_TMAC_TRCR_SEC_CCA_SEL, 0));
	mt76_wr(dev, MT_TMAC_TRCR1, val);

	val = MT_AGG_ACR_PKT_TIME_EN | MT_AGG_ACR_NO_BA_AR_RULE |
	      FIELD_PREP(MT_AGG_ACR_CFEND_RATE, 0x49) | /* 24M */
	      FIELD_PREP(MT_AGG_ACR_BAR_RATE, 0x4b); /* 6M */
	mt76_wr(dev, MT_AGG_ACR0, val);
	mt76_wr(dev, MT_AGG_ACR1, val);

	mt76_rmw_field(dev, MT_TMAC_CTCR0,
		       MT_TMAC_CTCR0_INS_DDLMT_REFTIME, 0x3f);
	mt76_rmw_field(dev, MT_TMAC_CTCR0,
		       MT_TMAC_CTCR0_INS_DDLMT_DENSITY, 0x3);
	mt76_rmw(dev, MT_TMAC_CTCR0,
		 MT_TMAC_CTCR0_INS_DDLMT_VHT_SMPDU_EN |
		 MT_TMAC_CTCR0_INS_DDLMT_EN,
		 MT_TMAC_CTCR0_INS_DDLMT_VHT_SMPDU_EN |
		 MT_TMAC_CTCR0_INS_DDLMT_EN);

	mt7615_mcu_set_rts_thresh(&dev->phy, 0x92b);
	mt7615_mac_set_scs(dev, true);

	mt76_rmw(dev, MT_AGG_SCR, MT_AGG_SCR_NLNAV_MID_PTEC_DIS,
		 MT_AGG_SCR_NLNAV_MID_PTEC_DIS);

	mt76_wr(dev, MT_DMA_DCR0, MT_DMA_DCR0_RX_VEC_DROP |
		FIELD_PREP(MT_DMA_DCR0_MAX_RX_LEN, 3072));

	mt76_wr(dev, MT_AGG_ARUCR,
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(0), 7) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(1), 2) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(2), 2) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(3), 2) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(4), 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(5), 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(6), 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(7), 1));

	mt76_wr(dev, MT_AGG_ARDCR,
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(0), MT7615_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(1), MT7615_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(2), MT7615_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(3), MT7615_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(4), MT7615_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(5), MT7615_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(6), MT7615_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(7), MT7615_RATE_RETRY - 1));

	mt76_wr(dev, MT_AGG_ARCR,
		(FIELD_PREP(MT_AGG_ARCR_RTS_RATE_THR, 2) |
		 MT_AGG_ARCR_RATE_DOWN_RATIO_EN |
		 FIELD_PREP(MT_AGG_ARCR_RATE_DOWN_RATIO, 1) |
		 FIELD_PREP(MT_AGG_ARCR_RATE_UP_EXTRA_TH, 4)));

	mask = MT_DMA_RCFR0_MCU_RX_MGMT |
	       MT_DMA_RCFR0_MCU_RX_CTL_NON_BAR |
	       MT_DMA_RCFR0_MCU_RX_CTL_BAR |
	       MT_DMA_RCFR0_MCU_RX_BYPASS |
	       MT_DMA_RCFR0_RX_DROPPED_UCAST |
	       MT_DMA_RCFR0_RX_DROPPED_MCAST;
	set = FIELD_PREP(MT_DMA_RCFR0_RX_DROPPED_UCAST, 2) |
	      FIELD_PREP(MT_DMA_RCFR0_RX_DROPPED_MCAST, 2);
	mt76_rmw(dev, MT_DMA_BN0RCFR0, mask, set);
	mt76_rmw(dev, MT_DMA_BN1RCFR0, mask, set);

	for (i = 0; i < MT7615_WTBL_SIZE; i++)
		mt7615_mac_wtbl_update(dev, i,
				       MT_WTBL_UPDATE_ADM_COUNT_CLEAR);

	mt76_set(dev, MT_WF_RMAC_MIB_TIME0, MT_WF_RMAC_MIB_RXTIME_EN);
	mt76_set(dev, MT_WF_RMAC_MIB_AIRTIME0, MT_WF_RMAC_MIB_RXTIME_EN);
}

bool mt7615_wait_for_mcu_init(struct mt7615_dev *dev)
{
	flush_work(&dev->mcu_work);

	return test_bit(MT76_STATE_MCU_RUNNING, &dev->mphy.state);
}

static void mt7615_init_work(struct work_struct *work)
{
	struct mt7615_dev *dev = container_of(work, struct mt7615_dev, mcu_work);

	if (mt7615_mcu_init(dev))
		return;

	mt7615_mcu_set_eeprom(dev);
	mt7615_mac_init(dev);
	mt7615_phy_init(dev);
	mt7615_mcu_del_wtbl_all(dev);
}

static int mt7615_init_hardware(struct mt7615_dev *dev)
{
	int ret, idx;

	mt76_wr(dev, MT_INT_SOURCE_CSR, ~0);

	INIT_WORK(&dev->mcu_work, mt7615_init_work);
	spin_lock_init(&dev->token_lock);
	idr_init(&dev->token);

	ret = mt7615_eeprom_init(dev);
	if (ret < 0)
		return ret;

	ret = mt7615_dma_init(dev);
	if (ret)
		return ret;

	set_bit(MT76_STATE_INITIALIZED, &dev->mphy.state);

	/* Beacon and mgmt frames should occupy wcid 0 */
	idx = mt76_wcid_alloc(dev->mt76.wcid_mask, MT7615_WTBL_STA - 1);
	if (idx)
		return -ENOSPC;

	dev->mt76.global_wcid.idx = idx;
	dev->mt76.global_wcid.hw_key_idx = -1;
	rcu_assign_pointer(dev->mt76.wcid[idx], &dev->mt76.global_wcid);

	return 0;
}

#define CCK_RATE(_idx, _rate) {						\
	.bitrate = _rate,						\
	.flags = IEEE80211_RATE_SHORT_PREAMBLE,				\
	.hw_value = (MT_PHY_TYPE_CCK << 8) | (_idx),			\
	.hw_value_short = (MT_PHY_TYPE_CCK << 8) | (4 + (_idx)),	\
}

#define OFDM_RATE(_idx, _rate) {					\
	.bitrate = _rate,						\
	.hw_value = (MT_PHY_TYPE_OFDM << 8) | (_idx),			\
	.hw_value_short = (MT_PHY_TYPE_OFDM << 8) | (_idx),		\
}

static struct ieee80211_rate mt7615_rates[] = {
	CCK_RATE(0, 10),
	CCK_RATE(1, 20),
	CCK_RATE(2, 55),
	CCK_RATE(3, 110),
	OFDM_RATE(11, 60),
	OFDM_RATE(15, 90),
	OFDM_RATE(10, 120),
	OFDM_RATE(14, 180),
	OFDM_RATE(9,  240),
	OFDM_RATE(13, 360),
	OFDM_RATE(8,  480),
	OFDM_RATE(12, 540),
};

static const struct ieee80211_iface_limit if_limits[] = {
	{
		.max = 1,
		.types = BIT(NL80211_IFTYPE_ADHOC)
	}, {
		.max = MT7615_MAX_INTERFACES,
		.types = BIT(NL80211_IFTYPE_AP) |
#ifdef CONFIG_MAC80211_MESH
			 BIT(NL80211_IFTYPE_MESH_POINT) |
#endif
			 BIT(NL80211_IFTYPE_STATION)
	}
};

static const struct ieee80211_iface_combination if_comb[] = {
	{
		.limits = if_limits,
		.n_limits = ARRAY_SIZE(if_limits),
		.max_interfaces = 4,
		.num_different_channels = 1,
		.beacon_int_infra_match = true,
		.radar_detect_widths = BIT(NL80211_CHAN_WIDTH_20_NOHT) |
				       BIT(NL80211_CHAN_WIDTH_20) |
				       BIT(NL80211_CHAN_WIDTH_40) |
				       BIT(NL80211_CHAN_WIDTH_80) |
				       BIT(NL80211_CHAN_WIDTH_160) |
				       BIT(NL80211_CHAN_WIDTH_80P80),
	}
};

static void
mt7615_init_txpower(struct mt7615_dev *dev,
		    struct ieee80211_supported_band *sband)
{
	int i, n_chains = hweight8(dev->mphy.antenna_mask), target_chains;
	u8 *eep = (u8 *)dev->mt76.eeprom.data;
	enum nl80211_band band = sband->band;

	target_chains = mt7615_ext_pa_enabled(dev, band) ? 1 : n_chains;
	for (i = 0; i < sband->n_channels; i++) {
		struct ieee80211_channel *chan = &sband->channels[i];
		u8 target_power = 0;
		int j;

		for (j = 0; j < target_chains; j++) {
			int index;

			index = mt7615_eeprom_get_power_index(dev, chan, j);
			target_power = max(target_power, eep[index]);
		}

		target_power = DIV_ROUND_UP(target_power, 2);
		switch (n_chains) {
		case 4:
			target_power += 6;
			break;
		case 3:
			target_power += 4;
			break;
		case 2:
			target_power += 3;
			break;
		default:
			break;
		}

		chan->max_power = min_t(int, chan->max_reg_power,
					target_power);
		chan->orig_mpwr = target_power;
	}
}

static void
mt7615_regd_notifier(struct wiphy *wiphy,
		     struct regulatory_request *request)
{
	struct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	struct mt7615_dev *dev = mt7615_hw_dev(hw);
	struct mt76_phy *mphy = hw->priv;
	struct mt7615_phy *phy = mphy->priv;
	struct cfg80211_chan_def *chandef = &mphy->chandef;

	dev->mt76.region = request->dfs_region;

	if (!(chandef->chan->flags & IEEE80211_CHAN_RADAR))
		return;

	mt7615_dfs_init_radar_detector(phy);
}

static void
mt7615_init_wiphy(struct ieee80211_hw *hw)
{
	struct mt7615_phy *phy = mt7615_hw_phy(hw);
	struct wiphy *wiphy = hw->wiphy;

	hw->queues = 4;
	hw->max_rates = 3;
	hw->max_report_rates = 7;
	hw->max_rate_tries = 11;

	phy->slottime = 9;

	hw->sta_data_size = sizeof(struct mt7615_sta);
	hw->vif_data_size = sizeof(struct mt7615_vif);

	wiphy->iface_combinations = if_comb;
	wiphy->n_iface_combinations = ARRAY_SIZE(if_comb);
	wiphy->reg_notifier = mt7615_regd_notifier;
	wiphy->flags |= WIPHY_FLAG_HAS_CHANNEL_SWITCH;

	wiphy_ext_feature_set(wiphy, NL80211_EXT_FEATURE_VHT_IBSS);

	ieee80211_hw_set(hw, TX_STATUS_NO_AMPDU_LEN);

	hw->max_tx_fragments = MT_TXP_MAX_BUF_NUM;
}

static void
mt7615_cap_dbdc_enable(struct mt7615_dev *dev)
{
	dev->mphy.sband_5g.sband.vht_cap.cap &=
			~(IEEE80211_VHT_CAP_SHORT_GI_160 |
			  IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ);
	if (dev->chainmask == 0xf)
		dev->mphy.antenna_mask = dev->chainmask >> 2;
	else
		dev->mphy.antenna_mask = dev->chainmask >> 1;
	dev->phy.chainmask = dev->mphy.antenna_mask;
	mt76_set_stream_caps(&dev->mt76, true);
}

static void
mt7615_cap_dbdc_disable(struct mt7615_dev *dev)
{
	dev->mphy.sband_5g.sband.vht_cap.cap |=
			IEEE80211_VHT_CAP_SHORT_GI_160 |
			IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ;
	dev->mphy.antenna_mask = dev->chainmask;
	dev->phy.chainmask = dev->chainmask;
	mt76_set_stream_caps(&dev->mt76, true);
}

int mt7615_register_ext_phy(struct mt7615_dev *dev)
{
	struct mt7615_phy *phy = mt7615_ext_phy(dev);
	struct mt76_phy *mphy;
	int ret;

	if (test_bit(MT76_STATE_RUNNING, &dev->mphy.state))
		return -EINVAL;

	if (phy)
		return 0;

	mt7615_cap_dbdc_enable(dev);
	mphy = mt76_alloc_phy(&dev->mt76, sizeof(*phy), &mt7615_ops);
	if (!mphy)
		return -ENOMEM;

	phy = mphy->priv;
	phy->dev = dev;
	phy->mt76 = mphy;
	phy->chainmask = dev->chainmask & ~dev->phy.chainmask;
	mphy->antenna_mask = BIT(hweight8(phy->chainmask)) - 1;
	mt7615_init_wiphy(mphy->hw);

	/* second phy can only handle 5 GHz */
	mphy->sband_2g.sband.n_channels = 0;
	mphy->hw->wiphy->bands[NL80211_BAND_2GHZ] = NULL;

	ret = mt76_register_phy(mphy);
	if (ret)
		ieee80211_free_hw(mphy->hw);

	return ret;
}

void mt7615_unregister_ext_phy(struct mt7615_dev *dev)
{
	struct mt7615_phy *phy = mt7615_ext_phy(dev);
	struct mt76_phy *mphy = dev->mt76.phy2;

	if (!phy)
		return;

	mt7615_cap_dbdc_disable(dev);
	mt76_unregister_phy(mphy);
	ieee80211_free_hw(mphy->hw);
}


int mt7615_register_device(struct mt7615_dev *dev)
{
	struct ieee80211_hw *hw = mt76_hw(dev);
	int ret;

	dev->phy.dev = dev;
	dev->phy.mt76 = &dev->mt76.phy;
	dev->mt76.phy.priv = &dev->phy;
	INIT_DELAYED_WORK(&dev->mt76.mac_work, mt7615_mac_work);
	INIT_LIST_HEAD(&dev->sta_poll_list);
	spin_lock_init(&dev->sta_poll_lock);

	ret = mt7615_init_hardware(dev);
	if (ret)
		return ret;

	mt7615_init_wiphy(hw);
	dev->mphy.sband_2g.sband.ht_cap.cap |= IEEE80211_HT_CAP_LDPC_CODING;
	dev->mphy.sband_5g.sband.ht_cap.cap |= IEEE80211_HT_CAP_LDPC_CODING;
	dev->mphy.sband_5g.sband.vht_cap.cap |=
			IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454 |
			IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK;
	mt7615_cap_dbdc_disable(dev);
	dev->phy.dfs_state = -1;

	ret = mt76_register_device(&dev->mt76, true, mt7615_rates,
				   ARRAY_SIZE(mt7615_rates));
	if (ret)
		return ret;

	ieee80211_queue_work(mt76_hw(dev), &dev->mcu_work);
	mt7615_init_txpower(dev, &dev->mphy.sband_2g.sband);
	mt7615_init_txpower(dev, &dev->mphy.sband_5g.sband);

	return mt7615_init_debugfs(dev);
}

void mt7615_unregister_device(struct mt7615_dev *dev)
{
	struct mt76_txwi_cache *txwi;
	bool mcu_running;
	int id;

	mcu_running = mt7615_wait_for_mcu_init(dev);

	mt7615_unregister_ext_phy(dev);
	mt76_unregister_device(&dev->mt76);
	if (mcu_running)
		mt7615_mcu_exit(dev);
	mt7615_dma_cleanup(dev);

	spin_lock_bh(&dev->token_lock);
	idr_for_each_entry(&dev->token, txwi, id) {
		mt7615_txp_skb_unmap(&dev->mt76, txwi);
		if (txwi->skb)
			dev_kfree_skb_any(txwi->skb);
		mt76_put_txwi(&dev->mt76, txwi);
	}
	spin_unlock_bh(&dev->token_lock);
	idr_destroy(&dev->token);

	mt76_free_device(&dev->mt76);
}
