#ifndef __AP_ACL_V2_H__
#define __AP_ACL_V2_H__

#include "link_list.h"

typedef enum FBT_IOT_PEER {
	FBT_IOT_PEER_UNKNOWN 					= 0x00000001,
	FBT_IOT_PEER_REALTEK 						= 0x00000002,
	FBT_IOT_PEER_REALTEK_92SE 				= 0x00000004,
	FBT_IOT_PEER_BROADCOM 					= 0x00000008,
	FBT_IOT_PEER_RALINK 						= 0x00000010,
	FBT_IOT_PEER_ATHEROS 						= 0x00000020,
	FBT_IOT_PEER_CISCO 						= 0x00000040,
	FBT_IOT_PEER_MERU 						= 0x00000080,
	FBT_IOT_PEER_MARVEL 						= 0x00000100,
	FBT_IOT_PEER_REALTEK_SOFTAP 				= 0x00000200,
	FBT_IOT_PEER_SELF_SOFTAP 				= 0x00000400,
	FBT_IOT_PEER_AIRGO 						= 0x00000800,
	FBT_IOT_PEER_INTEL 						= 0x00001000,
	FBT_IOT_PEER_RTK_APCLIENT				= 0x00002000,
	FBT_IOT_PEER_REALTEK_81XX				= 0x00004000,
	FBT_IOT_PEER_REALTEK_WOW				= 0x00008000,
	FBT_IOT_PEER_HTC							= 0x00010000,
	FBT_IOT_PEER_MAX							= 0x00020000,
}FBT_IOT_PEER_E, *PFBT_IOT_PEER_E;


#define OUI_LEN 3

#define MAX_NUM_OF_ACL_V2_MAC				64
#define MAX_NUM_OF_ACL_V2_OUI				64

typedef struct _OUI_ENTRY {
	UINT32 ID;
	UCHAR OUI[OUI_LEN];
}OUI_ENTRY, *POUI_ENTRY;


typedef struct _ACL_MAC_CTRL {
	DL_LIST List;
	UCHAR MACAddr[MAC_ADDR_LEN];
	ULONG SetTime;
} ACL_MAC_CTRL, *PACL_MAC_CTRL;

typedef struct _ACL_OUI_CTRL {
	DL_LIST List;
	UCHAR OUI[OUI_LEN];
	ULONG SetTime;
} ACL_OUI_CTRL, *PACL_OUI_CTRL; 


typedef struct _ACL_V2_CTRL {
	BOOLEAN OUI_Enable;
	BOOLEAN MAC_Enable;
	UINT32 OUI_ListNum;
	UINT32 MAC_ListNum;

	PRTMP_ADAPTER pAd;
	
	ULONG BlockTime; // seconds to age out the MAC & OUI List Entry
	RALINK_TIMER_STRUCT AgeOutTimer;
	BOOLEAN AgeOutTimer_Running;

	RTMP_OS_SEM OUI_ListLock;
	RTMP_OS_SEM MAC_ListLock;
	
	DL_LIST OUI_List;
	DL_LIST MAC_List;
} ACL_V2_CTRL, *PACL_V2_CTRL;

VOID ACL_V2_AgeOut(
IN	PACL_V2_CTRL	pACLCtrl);

VOID ACL_V2_CtrlInit(
	IN	PRTMP_ADAPTER	pAd);

VOID ACL_V2_CtrlExit(
	IN	PRTMP_ADAPTER	pAd);

BOOLEAN ACL_V2_List_Check(
	IN RTMP_ADAPTER *pAd,
	IN UCHAR *pAddr,
	IN UCHAR Apidx);

INT	Set_ACL_V2_DisConnectSta_Proc(
	IN	PRTMP_ADAPTER	pAd,
	IN	RTMP_STRING *arg);

INT	Set_ACL_V2_DisConnectOUI_Proc(
	IN	PRTMP_ADAPTER	pAd,
	IN	RTMP_STRING *arg);

INT	Show_ACL_V2_STAEntry_Proc(
	IN	PRTMP_ADAPTER	pAd,
	IN	RTMP_STRING *arg);

INT	Show_ACL_V2_OUI_Proc(
	IN	PRTMP_ADAPTER	pAd,
	IN	RTMP_STRING *arg);

UINT32 Set_ACL_V2_AddSTAEntry_Proc(
	IN PRTMP_ADAPTER pAd,
	IN PUCHAR pTargetMACAddr);

VOID Set_ACL_V2_DelSTAEntry_Proc(
	IN PRTMP_ADAPTER pAd,
	IN PUCHAR pTargetMACAddr);

UINT32 Set_ACL_V2_AddOUIEntry_Proc(
	IN PRTMP_ADAPTER pAd,
	IN PUCHAR pTargetOUIAddr);

VOID Set_ACL_V2_DelOUIEntry_Proc(
	IN PRTMP_ADAPTER pAd,
	IN PUCHAR pTargetOUIAddr);

VOID Set_ACL_V2_EntryExpire_Proc(
	IN	PRTMP_ADAPTER	pAd,
	IN	RTMP_STRING *arg);

VOID Show_ACL_V2_EntryExpire_Proc(
	IN	PRTMP_ADAPTER	pAd,
	IN	RTMP_STRING *arg);

#endif /* __AP_ACL_V2_H__ */
