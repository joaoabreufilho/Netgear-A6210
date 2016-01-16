/****************************************************************************

    Module Name:
	rt_os_util.h

	Abstract:
	All function prototypes are provided from UTIL modules.

	Note:
	But can not use any OS key word and compile option here.
	All functions are provided from UTIL modules.


***************************************************************************/

#ifndef __RT_OS_UTIL_H__
#define __RT_OS_UTIL_H__

/* ============================ rt_linux.c ================================== */
/* General */
void RtmpUtilInit(void);

/* OS Time */
void RtmpusecDelay(ULONG usec);
void RtmpOsMsDelay(ULONG msec);
void RTMP_GetCurrentSystemTime(LARGE_INTEGER *time);
ULONG RTMPMsecsToJiffies(UINT msec);
void RTMP_GetCurrentSystemTick(ULONG *pNow);
void RtmpOsWait(UINT32 Time);
UINT32 RtmpOsTimerAfter(ULONG a, ULONG b);
UINT32 RtmpOsTimerBefore(ULONG a, ULONG b);
void RtmpOsGetSystemUpTime(ULONG *pTime);
UINT32 RtmpOsTickUnitGet(void);
NDIS_STATUS os_alloc_mem(void *pReserved, UCHAR **mem, ULONG size);
NDIS_STATUS os_alloc_mem_suspend(void *pReserved, UCHAR **mem, ULONG size);
void os_free_mem(void *pReserved, void *mem);
NDIS_STATUS AdapterBlockAllocateMemory(void *handle, void **ppAd, UINT32 SizeOfpAd);
void *RtmpOsVmalloc(ULONG Size);
void RtmpOsVfree(void *pMem);
ULONG RtmpOsCopyFromUser(void *to, const void *from, ULONG n);
ULONG RtmpOsCopyToUser(void *to, const void *from, ULONG n);
BOOLEAN RtmpOsStatsAlloc(void **ppStats, void **ppIwStats);

/* OS Packet */
PNDIS_PACKET RtmpOSNetPktAlloc(void *pReserved, int size);

PNDIS_PACKET RTMP_AllocateFragPacketBuffer(void *pReserved, ULONG Length);

NDIS_STATUS RTMPAllocateNdisPacket(void *pReserved, PNDIS_PACKET *ppPacket,
	PUCHAR pHeader, UINT HeaderLen, PUCHAR pData, UINT DataLen);

void RTMPFreeNdisPacket(void *pReserved, PNDIS_PACKET pPacket);

void RTMP_QueryPacketInfo(PNDIS_PACKET pPacket, PACKET_INFO *pPacketInfo,
	PUCHAR *pSrcBufVA, UINT *pSrcBufLen);

PNDIS_PACKET DuplicatePacket(PNET_DEV pNetDev, PNDIS_PACKET pPacket, 
	UCHAR FromWhichBSSID);

PNDIS_PACKET duplicate_pkt(PNET_DEV pNetDev, PUCHAR pHeader802_3, UINT HdrLen,
	PUCHAR pData, ULONG DataSize, UCHAR FromWhichBSSID);

PNDIS_PACKET duplicate_pkt_with_TKIP_MIC(void *pReserved, PNDIS_PACKET pOldPkt);

PNDIS_PACKET duplicate_pkt_with_VLAN(PNET_DEV pNetDev, USHORT VLAN_VID,
	USHORT VLAN_Priority, PUCHAR pHeader802_3, UINT HdrLen, PUCHAR pData,
	ULONG DataSize, UCHAR FromWhichBSSID, UCHAR *TPID);

typedef void (*RTMP_CB_8023_PACKET_ANNOUNCE)(void *pCtrlBkPtr, PNDIS_PACKET pPacket,
	UCHAR OpMode);

BOOLEAN RTMPL2FrameTxAction(void *pCtrlBkPtr, PNET_DEV pNetDev,
	RTMP_CB_8023_PACKET_ANNOUNCE _announce_802_3_packet, UCHAR apidx,
	PUCHAR pData, UINT32 data_len, UCHAR OpMode);

PNDIS_PACKET ExpandPacket(void *pReserved, PNDIS_PACKET pPacket, UINT32 ext_head_len,
	UINT32 ext_tail_len);

PNDIS_PACKET ClonePacket(void *pReserved, PNDIS_PACKET pPacket, PUCHAR pData,
	ULONG DataSize);

void wlan_802_11_to_802_3_packet(PNET_DEV pNetDev, UCHAR OpMode, USHORT VLAN_VID,
	USHORT VLAN_Priority, PNDIS_PACKET pRxPacket, UCHAR *pData, ULONG DataSize,
	PUCHAR pHeader802_3, UCHAR FromWhichBSSID, UCHAR *TPID);

UCHAR VLAN_8023_Header_Copy(USHORT VLAN_VID, USHORT VLAN_Priority, PUCHAR pHeader802_3,
	UINT HdrLen, PUCHAR pData, UCHAR FromWhichBSSID, UCHAR *TPID);

void RtmpOsPktBodyCopy(PNET_DEV pNetDev, PNDIS_PACKET pNetPkt, ULONG ThisFrameLen,
	PUCHAR pData);

int RtmpOsIsPktCloned(PNDIS_PACKET pNetPkt);
PNDIS_PACKET RtmpOsPktCopy(PNDIS_PACKET pNetPkt);
PNDIS_PACKET RtmpOsPktClone(PNDIS_PACKET pNetPkt);

void RtmpOsPktDataPtrAssign(PNDIS_PACKET pNetPkt, UCHAR *pData);
void RtmpOsPktLenAssign(PNDIS_PACKET pNetPkt, LONG Len);
void RtmpOsPktTailAdjust(PNDIS_PACKET pNetPkt, UINT removedTagLen);
PUCHAR RtmpOsPktTailBufExtend(PNDIS_PACKET pNetPkt, UINT len);
PUCHAR RtmpOsPktHeadBufExtend(PNDIS_PACKET pNetPkt, UINT len);
void RtmpOsPktReserve(PNDIS_PACKET pNetPkt, UINT len);
void RtmpOsPktProtocolAssign(PNDIS_PACKET pNetPkt);
void RtmpOsPktInfPpaSend(PNDIS_PACKET pNetPkt);
void RtmpOsPktRcvHandle(PNDIS_PACKET pNetPkt);
void RtmpOsPktNatMagicTag(PNDIS_PACKET pNetPkt);
void RtmpOsPktNatNone(PNDIS_PACKET pNetPkt);
void RtmpOsPktInit(PNDIS_PACKET pNetPkt, PNET_DEV pNetDev, UCHAR *buf, USHORT len);

PNDIS_PACKET RtmpOsPktIappMakeUp(PNET_DEV pNetDev, UINT8 *pMac);

BOOLEAN RtmpOsPktOffsetInit(void);
UINT16 RtmpOsNtohs(UINT16 Value);
UINT16 RtmpOsHtons(UINT16 Value);
UINT32 RtmpOsNtohl(UINT32 Value);
UINT32 RtmpOsHtonl(UINT32 Value);

/* OS File */
RTMP_OS_FD RtmpOSFileOpen(char *pPath,  int flag, int mode);
int RtmpOSFileClose(RTMP_OS_FD osfd);
void RtmpOSFileSeek(RTMP_OS_FD osfd, int offset);
int RtmpOSFileRead(RTMP_OS_FD osfd, char *pDataPtr, int readLen);
int RtmpOSFileWrite(RTMP_OS_FD osfd, char *pDataPtr, int writeLen);

INT32 RtmpOsFileIsErr(void *pFile);

void RtmpOSFSInfoChange(RTMP_OS_FS_INFO *pOSFSInfoOrg, BOOLEAN bSet);

/* OS Network Interface */
int RtmpOSNetDevAddrSet(UCHAR OpMode, PNET_DEV pNetDev, PUCHAR pMacAddr,
	PUCHAR dev_name);

void RtmpOSNetDevClose(PNET_DEV pNetDev);
void RtmpOSNetDevFree(PNET_DEV pNetDev);

#ifdef CONFIG_STA_SUPPORT
int RtmpOSNotifyRawData(PNET_DEV pNetDev, UCHAR *buf, int len, ULONG type, USHORT proto);
#endif

void RtmpOSNetDevDetach(PNET_DEV pNetDev);
int RtmpOSNetDevAttach(UCHAR OpMode, PNET_DEV pNetDev, RTMP_OS_NETDEV_OP_HOOK *pDevOpHook);

void RtmpOSNetDevProtect(BOOLEAN lock_it);

PNET_DEV RtmpOSNetDevCreate(INT32 MC_RowID, UINT32 *pIoctlIF, int devType,
	int devNum, int privMemSize, PSTRING pNamePrefix);

BOOLEAN RtmpOSNetDevIsUp(void *pDev);
unsigned char *RtmpOsNetDevGetPhyAddr(void *pDev);
void RtmpOsNetQueueStart(PNET_DEV pDev);
void RtmpOsNetQueueStop(PNET_DEV pDev);
void RtmpOsNetQueueWake(PNET_DEV pDev);
void RtmpOsSetPktNetDev(void *pPkt, void *pDev);
PNET_DEV RtmpOsPktNetDevGet(void *pPkt);
char *RtmpOsGetNetDevName(void *pDev);
UINT32 RtmpOsGetNetIfIndex( void *pDev);
void RtmpOsSetNetDevPriv(void *pDev, void *pPriv);
void *RtmpOsGetNetDevPriv(void *pDev);
void RtmpOsSetNetDevWdev(void *net_dev, void *wdev);
void *RtmpOsGetNetDevWdev(void *pDev);
USHORT RtmpDevPrivFlagsGet(void *pDev);
void RtmpDevPrivFlagsSet(void *pDev, USHORT PrivFlags);
void RtmpOsSetNetDevType(void *pDev, USHORT Type);
void RtmpOsSetNetDevTypeMonitor(void *pDev);
UCHAR get_sniffer_mode(void *pDev);
//void set_sniffer_mode(void *pDev, UCHAR mode);

/* OS Semaphore */

BOOLEAN RtmpOsSemaInitLocked(RTMP_OS_SEM *pSemOrg, LIST_HEADER *pSemList);
BOOLEAN RtmpOsSemaInit(RTMP_OS_SEM *pSemOrg, LIST_HEADER *pSemList);
BOOLEAN RtmpOsSemaDestory(RTMP_OS_SEM *pSemOrg);
int RtmpOsSemaWaitInterruptible(RTMP_OS_SEM *pSemOrg);
void RtmpOsSemaWakeUp(RTMP_OS_SEM *pSemOrg);
void RtmpOsCmdUp(RTMP_OS_TASK *pCmdQTask);
void RtmpOsMlmeUp(RTMP_OS_TASK *pMlmeQTask);
void RtmpOsInitCompletion(RTMP_OS_COMPLETION *pCompletion);
void RtmpOsExitCompletion(RTMP_OS_COMPLETION *pCompletion);
BOOLEAN RtmpOsComplete(RTMP_OS_COMPLETION *pCompletion);
ULONG RtmpOsWaitForCompletionTimeout(RTMP_OS_COMPLETION *pCompletion, ULONG Timeout); 

/* OS Task */
BOOLEAN RtmpOsTaskletSche(RTMP_NET_TASK_STRUCT *pTasklet);

BOOLEAN RtmpOsTaskletInit(RTMP_NET_TASK_STRUCT *pTasklet, 
	void (*pFunc)(unsigned long data), ULONG Data, LIST_HEADER *pTaskletList);

BOOLEAN RtmpOsTaskletKill(RTMP_NET_TASK_STRUCT *pTasklet);
void RtmpOsTaskletDataAssign(RTMP_NET_TASK_STRUCT *pTasklet, ULONG Data);

void RtmpOsTaskWakeUp(RTMP_OS_TASK *pTaskOrg);
//INT32 RtmpOsTaskIsKilled(RTMP_OS_TASK *pTaskOrg);

BOOLEAN RtmpOsCheckTaskLegality(RTMP_OS_TASK *pTaskOrg);
BOOLEAN RtmpOSTaskAlloc(RTMP_OS_TASK *pTask, LIST_HEADER *pTaskList);
void RtmpOSTaskFree(RTMP_OS_TASK *pTask);
NDIS_STATUS RtmpOSTaskKill(RTMP_OS_TASK *pTaskOrg);
int RtmpOSTaskNotifyToExit(RTMP_OS_TASK *pTaskOrg);
void RtmpOSTaskCustomize(RTMP_OS_TASK *pTaskOrg);

NDIS_STATUS RtmpOSTaskAttach(RTMP_OS_TASK *pTaskOrg, RTMP_OS_TASK_CALLBACK fn,
	ULONG arg);

NDIS_STATUS RtmpOSTaskInit(RTMP_OS_TASK *pTaskOrg, PSTRING pTaskName, void *pPriv,
	LIST_HEADER *pTaskList, LIST_HEADER *pSemList);

BOOLEAN RtmpOSTaskWait(void *pReserved, RTMP_OS_TASK *pTaskOrg, INT32 *pStatus);

//void *RtmpOsTaskDataGet(RTMP_OS_TASK *pTaskOrg);

INT32 RtmpThreadPidKill(RTMP_OS_PID PID);

/* OS Cache */
void RtmpOsDCacheFlush(ULONG AddrStart, ULONG Size);

/* OS Timer */
void RTMP_SetPeriodicTimer(NDIS_MINIPORT_TIMER *pTimerOrg, unsigned long timeout);

void RTMP_OS_Init_Timer(void *pReserved, NDIS_MINIPORT_TIMER *pTimerOrg, 
	TIMER_FUNCTION function, PVOID data, LIST_HEADER *pTimerList);

void RTMP_OS_Add_Timer(NDIS_MINIPORT_TIMER *pTimerOrg, unsigned long timeout);
void RTMP_OS_Mod_Timer(NDIS_MINIPORT_TIMER *pTimerOrg, unsigned long timeout);
void RTMP_OS_Del_Timer(NDIS_MINIPORT_TIMER *pTimerOrg, BOOLEAN *pCancelled);
void RTMP_OS_Release_Timer(NDIS_MINIPORT_TIMER *pTimerOrg);

BOOLEAN RTMP_OS_Alloc_Rsc(LIST_HEADER *pRscList, void *pRsc, UINT32 RscLen);
void RTMP_OS_Free_Rscs(LIST_HEADER *pRscList);

/* OS Lock */
BOOLEAN RtmpOsAllocateLock(NDIS_SPIN_LOCK *pLock, LIST_HEADER *pLockList);
void RtmpOsFreeSpinLock(NDIS_SPIN_LOCK *pLockOrg);
void RtmpOsSpinLockBh(NDIS_SPIN_LOCK *pLockOrg);
void RtmpOsSpinUnLockBh(NDIS_SPIN_LOCK *pLockOrg);
void RtmpOsIntLock(NDIS_SPIN_LOCK *pLockOrg, ULONG *pIrqFlags);
void RtmpOsIntUnLock(NDIS_SPIN_LOCK *pLockOrg, ULONG IrqFlags);

/* OS PID */
void RtmpOsGetPid(ULONG *pDst, ULONG PID);
void RtmpOsTaskPidInit(RTMP_OS_PID *pPid);

/* OS Wireless */
ULONG RtmpOsMaxScanDataGet(void);

/* OS Interrutp */
INT32 RtmpOsIsInInterrupt(void);

/* OS USB */
void *RtmpOsUsbUrbDataGet(void *pUrb);
NTSTATUS RtmpOsUsbUrbStatusGet(void *pUrb);
ULONG RtmpOsUsbUrbLenGet(void *pUrb);

/* OS Atomic */
BOOLEAN RtmpOsAtomicInit(RTMP_OS_ATOMIC *pAtomic, LIST_HEADER *pAtomicList);
void RtmpOsAtomicDestroy(RTMP_OS_ATOMIC *pAtomic);
LONG RtmpOsAtomicRead(RTMP_OS_ATOMIC *pAtomic);
void RtmpOsAtomicDec(RTMP_OS_ATOMIC *pAtomic);
void RtmpOsAtomicInterlockedExchange(RTMP_OS_ATOMIC *pAtomicSrc, LONG Value);

/* OS Utility */
void hex_dump(char *str, unsigned char *pSrcBufVA, unsigned int SrcBufLen);

typedef void (*RTMP_OS_SEND_WLAN_EVENT)(void *pAdSrc, USHORT Event_flag,
	PUCHAR pAddr, UCHAR BssIdx, CHAR Rssi);

void RtmpOsSendWirelessEvent(void *pAd, USHORT Event_flag, PUCHAR pAddr,
	UCHAR BssIdx, CHAR Rssi, RTMP_OS_SEND_WLAN_EVENT pFunc);

#ifdef CONFIG_AP_SUPPORT
void SendSignalToDaemon(int sig, RTMP_OS_PID pid, unsigned long pid_no);
#endif

int RtmpOSWrielessEventSend(PNET_DEV pNetDev, UINT32 eventType, int flags,
	PUCHAR pSrcMac, PUCHAR pData, UINT32 dataLen);

int RtmpOSWrielessEventSendExt(PNET_DEV pNetDev, UINT32 eventType, int flags,
	PUCHAR pSrcMac, PUCHAR pData, UINT32 dataLen, UINT32 family);

UINT RtmpOsWirelessExtVerGet(void);

void RtmpDrvAllMacPrint(void *pReserved, UINT32 *pBufMac, UINT32 AddrStart,
	UINT32 AddrEnd, UINT32 AddrStep);

void RtmpDrvAllE2PPrint(void *pReserved, USHORT *pMacContent, UINT32 AddrEnd,
	UINT32 AddrStep);

void RtmpDrvAllRFPrint(void *pReserved, UCHAR *pBuf, UINT32 BufLen);
void RtmpOsWlanEventSet(void *pReserved, BOOLEAN *pCfgWEnt, BOOLEAN FlgIsWEntSup);
UINT16 RtmpOsGetUnaligned(UINT16 *pWord);
UINT32 RtmpOsGetUnaligned32(UINT32 *pWord);
ULONG RtmpOsGetUnalignedlong(ULONG *pWord);
long RtmpOsSimpleStrtol(const char *cp, char **endp, unsigned int base);
void RtmpOsOpsInit(RTMP_OS_ABL_OPS *pOps);

/* ============================ rt_os_util.c ================================ */
void RtmpDrvRateGet(void *pReserved, UINT8 MODE, UINT8 ShortGI, UINT8 BW,
	UINT8 MCS, UINT8 Antenna, ULONG *pRate);

char * rtstrchr(const char * s, int c);
PSTRING WscGetAuthTypeStr(USHORT authFlag);
PSTRING WscGetEncryTypeStr(USHORT encryFlag);
USHORT WscGetAuthTypeFromStr(PSTRING arg);
USHORT WscGetEncrypTypeFromStr(PSTRING arg);

void RtmpMeshDown(void *pDrvCtrlBK, BOOLEAN WaitFlag,
	BOOLEAN (*RtmpMeshLinkCheck)( void *pAd));

USHORT RtmpOsNetPrivGet(PNET_DEV pDev);

BOOLEAN RtmpOsCmdDisplayLenCheck(UINT32 LenSrc, UINT32 Offset);

void WpaSendMicFailureToWpaSupplicant(PNET_DEV pNetDev, const PUCHAR src_addr,
	BOOLEAN bUnicast, int key_id, const PUCHAR tsc);

int wext_notify_event_assoc(PNET_DEV pNetDev, UCHAR *ReqVarIEs, UINT32 ReqVarIELen);

void SendAssocIEsToWpaSupplicant(PNET_DEV pNetDev, UCHAR *ReqVarIEs, UINT32 ReqVarIELen);

#ifdef CONFIG_STA_SUPPORT
#ifdef CONFIG_PM
#ifdef USB_SUPPORT_SELECTIVE_SUSPEND

int RTMP_Usb_AutoPM_Put_Interface(void *pUsb_Dev, void *intf);
int RTMP_Usb_AutoPM_Get_Interface(void *pUsb_Dev, void *intf);

#endif /* USB_SUPPORT_SELECTIVE_SUSPEND */
#endif /* CONFIG_PM */
#endif /* CONFIG_STA_SUPPORT */

ra_dma_addr_t linux_pci_map_single(void *pPciDev, void *ptr, size_t size, int sd_idx, int direction);

void linux_pci_unmap_single(void *pPciDev, ra_dma_addr_t dma_addr, size_t size, int direction);

/* ============================ rt_usb_util.c =============================== */
#ifdef RTMP_MAC_USB
typedef void (*USB_COMPLETE_HANDLER)(void *);

void dump_urb(void *purb);
int rausb_register(void * new_driver);
void rausb_deregister(void * driver);

/*struct urb *rausb_alloc_urb(int iso_packets); */

void rausb_free_urb(void *urb);
void rausb_put_dev(void *dev);
struct usb_device *rausb_get_dev(void *dev);
int rausb_submit_urb(void *urb);
void *rausb_buffer_alloc(void *dev, size_t size, ra_dma_addr_t *dma);
void rausb_buffer_free(void *dev, size_t size, void *addr, ra_dma_addr_t dma);

int rausb_control_msg(void *dev, unsigned int pipe, __u8 request, __u8 requesttype,
	__u16 value, __u16 index, void *data, __u16 size, int timeout);

void rausb_fill_bulk_urb(void *urb, void *dev, unsigned int pipe, 
	void *transfer_buffer, int buffer_length, USB_COMPLETE_HANDLER complete_fn,
	void *context);

unsigned int rausb_sndctrlpipe(void *dev, ULONG address);
unsigned int rausb_rcvctrlpipe(void *dev, ULONG address);
unsigned int rausb_sndbulkpipe(void *dev, ULONG address);
unsigned int rausb_rcvbulkpipe(void *dev, ULONG address);

void rausb_kill_urb(void *urb);

void RtmpOsUsbInitHTTxDesc(void *pUrbSrc, void *pUsb_Dev, UINT BulkOutEpAddr,
	PUCHAR pSrc, ULONG BulkOutSize, USB_COMPLETE_HANDLER Func,
	void *pTxContext, ra_dma_addr_t TransferDma);

void RtmpOsUsbInitRxDesc(void *pUrbSrc, void *pUsb_Dev, UINT BulkInEpAddr,
	UCHAR *pTransferBuffer, UINT32 BufSize, USB_COMPLETE_HANDLER Func,
	void *pRxContext, ra_dma_addr_t TransferDma);

void *RtmpOsUsbContextGet(void *pUrb);
NTSTATUS RtmpOsUsbStatusGet(void *pUrb);
void RtmpOsUsbDmaMapping(void *pUrb);
#endif /* RTMP_MAC_USB */

#if defined(RTMP_RBUS_SUPPORT) || defined(RTMP_FLASH_SUPPORT)
void RtmpFlashRead(UCHAR *p, ULONG a, ULONG b);
void RtmpFlashWrite(UCHAR *p, ULONG a, ULONG b);
#endif /* defined(RTMP_RBUS_SUPPORT) || defined(RTMP_FLASH_SUPPORT) */

UINT32 RtmpOsGetUsbDevVendorID(void *pUsbDev);
UINT32 RtmpOsGetUsbDevProductID(void *pUsbDev);

/* CFG80211 */
#ifdef RT_CFG80211_SUPPORT
typedef struct __CFG80211_BAND {
	UINT8 RFICType;
	UINT8 MpduDensity;
	UINT8 TxStream;
	UINT8 RxStream;
	UINT32 MaxTxPwr;
	UINT32 MaxBssTable;
	UINT16 RtsThreshold;
	UINT16 FragmentThreshold;
	UINT32 RetryMaxCnt; /* bit0~7: short; bit8 ~ 15: long */
	BOOLEAN FlgIsBMode;
} CFG80211_BAND;

void CFG80211OS_UnRegister(void *pCB, void *pNetDev);

BOOLEAN CFG80211_SupBandInit(void *pCB, CFG80211_BAND *pBandInfo, void *pWiphyOrg,
	void *pChannelsOrg, void *pRatesOrg);

BOOLEAN CFG80211OS_SupBandReInit(void *pCB, CFG80211_BAND *pBandInfo);
void CFG80211OS_RegHint(void *pCB, UCHAR *pCountryIe, ULONG CountryIeLen);
void CFG80211OS_RegHint11D(void *pCB, UCHAR *pCountryIe, ULONG CountryIeLen);

BOOLEAN CFG80211OS_BandInfoGet(void *pCB, void *pWiphyOrg, void **ppBand24,
	void **ppBand5);

UINT32 CFG80211OS_ChanNumGet(void *pCB, void *pWiphyOrg, UINT32 IdBand);

BOOLEAN CFG80211OS_ChanInfoGet(void *pCB, void *pWiphyOrg, UINT32 IdBand,
	UINT32 IdChan, UINT32 *pChanId, UINT32 *pPower, BOOLEAN *pFlgIsRadar);

BOOLEAN CFG80211OS_ChanInfoInit(void *pCB, UINT32 InfoIndex, UCHAR ChanId,
	UCHAR MaxTxPwr, BOOLEAN FlgIsNMode, BOOLEAN FlgIsBW20M);

void CFG80211OS_Scaning(void *pCB, UINT32 ChanId, UCHAR *pFrame, UINT32 FrameLen,
	INT32 RSSI, BOOLEAN FlgIsNMode, UINT8 BW);

void CFG80211OS_ScanEnd(void *pCB, BOOLEAN FlgIsAborted);

void CFG80211OS_ConnectResultInform(void *pCB, UCHAR *pBSSID, UCHAR *pReqIe,
	UINT32 ReqIeLen, UCHAR *pRspIe, UINT32 RspIeLen, UCHAR FlgIsSuccess);

void CFG80211OS_P2pClientConnectResultInform(PNET_DEV pNetDev, UCHAR *pBSSID,
	UCHAR *pReqIe, UINT32 ReqIeLen, UCHAR *pRspIe, UINT32 RspIeLen,
	UCHAR FlgIsSuccess);

BOOLEAN CFG80211OS_RxMgmt(PNET_DEV pNetDev, INT32 freq, PUCHAR frame, UINT32 len);

void CFG80211OS_TxStatus(PNET_DEV pNetDev, INT32 cookie, PUCHAR frame,
	UINT32 len, BOOLEAN ack);
void CFG80211OS_NewSta(PNET_DEV pNetDev, const PUCHAR mac_addr, 
	const PUCHAR assoc_frame,  UINT32 assoc_len);
void CFG80211OS_DelSta(PNET_DEV pNetDev, const PUCHAR mac_addr);
void CFG80211OS_MICFailReport(PNET_DEV pNetDev, const PUCHAR src_addr, 
	BOOLEAN unicast, int key_id, const PUCHAR tsc);
void CFG80211OS_Roamed(PNET_DEV pNetDev, UCHAR *pBSSID, UCHAR *pReqIe, 
	UINT32 ReqIeLen, UCHAR *pRspIe, UINT32 RspIeLen);
void CFG80211OS_RecvObssBeacon(void *pCB, const PUCHAR pFrame, int frameLen, 
	int freq);
#endif /* RT_CFG80211_SUPPORT */


/* ================================ MACRO =================================== */
#define RTMP_UTIL_DCACHE_FLUSH(__AddrStart, __Size)

/* ================================ EXTERN ================================== */
extern UCHAR SNAP_802_1H[6];
extern UCHAR SNAP_BRIDGE_TUNNEL[6];
extern UCHAR EAPOL[2];
extern UCHAR TPID[];
extern UCHAR IPX[2];
extern UCHAR APPLE_TALK[2];
extern UCHAR NUM_BIT8[8];
extern ULONG OS_NumOfMemAlloc, OS_NumOfMemFree;
extern UINT32 RalinkRate_Legacy[];
extern UINT32 RalinkRate_HT_1NSS[Rate_BW_MAX][Rate_GI_MAX][Rate_MCS];
extern UINT32 RalinkRate_VHT_1NSS[Rate_BW_MAX][Rate_GI_MAX][Rate_MCS];
extern UINT8 newRateGetAntenna(UINT8 MCS);

//#ifdef PLATFORM_UBM_IPX8
//#include "vrut_ubm.h"
//#endif

INT32  RtPrivIoctlSetVal(void);

void OS_SPIN_LOCK(NDIS_SPIN_LOCK *lock);
void OS_SPIN_UNLOCK(NDIS_SPIN_LOCK *lock);
void OS_SPIN_LOCK_IRQSAVE(NDIS_SPIN_LOCK *lock, unsigned long *flags);
void OS_SPIN_UNLOCK_IRQRESTORE(NDIS_SPIN_LOCK *lock, unsigned long *flags);
void OS_SPIN_LOCK_IRQ(NDIS_SPIN_LOCK *lock);
void OS_SPIN_UNLOCK_IRQ(NDIS_SPIN_LOCK *lock);
void RtmpOsSpinLockIrqSave(NDIS_SPIN_LOCK *lock, unsigned long *flags);
void RtmpOsSpinUnlockIrqRestore(NDIS_SPIN_LOCK *lock, unsigned long *flags);
void RtmpOsSpinLockIrq(NDIS_SPIN_LOCK *lock);
void RtmpOsSpinUnlockIrq(NDIS_SPIN_LOCK *lock);
int  OS_TEST_BIT(int bit, unsigned long *flags);
void OS_SET_BIT(int bit, unsigned long *flags);
void OS_CLEAR_BIT(int bit, unsigned long *flags);
void OS_LOAD_CODE_FROM_BIN(unsigned char **image, char *bin_name, void *inf_dev, UINT32 *code_len);

#endif /* __RT_OS_UTIL_H__ */
