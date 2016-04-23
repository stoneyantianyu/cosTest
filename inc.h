#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef unsigned char u1;
typedef unsigned short u2;
typedef unsigned int u4;

typedef char s1;
typedef short s2;
typedef int s4;


#define COS_MALLOC(size)			malloc(size)
#define COS_MEMSET(buf, val, size)	memset(buf, val, size)
#define COS_MEMCPY(buf, val, size)	memcpy(buf, val, size)

#define DEBUG

#ifdef DEBUG
#define PRINT_FUNC_NAME()	{printf("Func: ");printf(__FUNCTION__);printf("\n");}
#define PRINT_STR(s)			{printf("%s\n", s);}
#define PRINTGG()			{PRINT_STR("########");}
#else
#define PRINT_FUNC_NAME()	{}
#define PRINT_STR(s)			{}
#define PRINTGG()			{}
#endif




#define DF_MF			0x3F00
#define ADF_USIM			0x7FF0
#define DF_GSM_ACCESS	0x5F3B
#define DF_PHONEBOOK	0x5F3A
#define DF_TELECOM		0x7F10

#define EF_ACC			0x6F78
#define EF_ACL			0x6F57
#define EF_AD			0x6FAD
#define EF_ARR			0x2F06
#define EF_ARR_SUB		0x6F06
#define EF_DIR			0x2F00
#define EF_ECC			0x6FB7
#define EF_EHPLMN		0x6FD9
#define EF_EST			0x6F56
#define EF_FPLMN			0x6F7B
#define EF_HPLMNwAcT	0x6F62
#define EF_HPPLMN		0x6F31
#define EF_ICCID			0x2FE2
#define EF_IMSI			0x6F07
#define EF_Kc				0x4F20
#define EF_KcGPRS		0x4F52
#define EF_Keys			0x6F08
#define EF_KeysPS		0x6F09
#define EF_LI				0x6F05
#define EF_LOCI			0x6F7E
#define EF_NETPAR		0x6FC4
#define EF_OPL			0x6FC6
#define EF_OPLMNwAcT	0x6F61
#define EF_PL				0x2F05
#define EF_PLMNwAcT		0x6F60
#define EF_PNN			0x6FC5
#define EF_PSLOCI		0x6F73
#define EF_SPDI			0x6FCD
#define EF_SPN			0x6F46
#define EF_START_HFN	0x6F5B
#define EF_THRESHOLD	0x6F5C
#define EF_UST			0x6F38



typedef enum fileType {
	MF,
	ADF,
	DF,
	EF
}fileType;

typedef enum efType {
	transparent,
	linearfix,
	circle
}efType;

struct ArrRef;
struct FileList;
struct FileDesc;

typedef struct ArrRef{
	u2 arrFid;
	u1 arrRecordNum;
}ArrRef;


typedef struct FileList{
	struct FileDesc *me;
	struct FileList *next;
}FileList;

typedef struct FileDesc{
	u2 fid;
	u1 sfi;
	fileType filetype;
	efType eftype;
	struct ArrRef arrRef;
	u1* aid;
	struct FileDesc* parent;
	struct FileList* childEf;
	struct FileList* childDf;	
	
	u1* data;
	u2 fileLen;
	u1 recordLen;
	u1 recordCnt;
	u1 recordPointer;
}FileDesc;


void processSelect(char* apdu);
void processManageChannel(char* apdu);

extern FileDesc* buildFileSystem();
extern FileDesc* buildDFADF(u2 fid);
extern FileDesc* buildDF_MF();
extern FileDesc* buildDF_TELECOM();
extern FileDesc* buildDF_GSM_ACCESS();
extern FileDesc* buildDF_PHONEBOOK();
extern FileDesc* buildADF_USIM();

void addChildFile(FileList** pfileList, FileDesc* file);
void addChildEFs(FileList** pfileList, u2* fids, u2 len);
FileDesc* buildEFs(FileList** pfileList, u2* fids, u1 len);

FileDesc* creatEF_ACC();
FileDesc* creatEF_ACL();
FileDesc* creatEF_AD();
FileDesc* creatEF_ARR();
FileDesc* creatEF_ARR_SUB();
FileDesc* creatEF_DIR();
FileDesc* creatEF_ECC();
FileDesc* creatEF_EHPLMN();
FileDesc* creatEF_EST();
FileDesc* creatEF_FPLMN();
FileDesc* creatEF_HPLMNwAcT();
FileDesc* creatEF_HPPLMN();
FileDesc* creatEF_ICCID();
FileDesc* creatEF_IMSI();
FileDesc* creatEF_Kc();
FileDesc* creatEF_KcGPRS();
FileDesc* creatEF_Keys();
FileDesc* creatEF_KeysPS();
FileDesc* creatEF_LI();
FileDesc* creatEF_LOCI();
FileDesc* creatEF_NETPAR();
FileDesc* creatEF_OPL();
FileDesc* creatEF_OPLMNwAcT();
FileDesc* creatEF_PL();
FileDesc* creatEF_PLMNwAcT();
FileDesc* creatEF_PNN();
FileDesc* creatEF_PSLOCI();
FileDesc* creatEF_SPDI();
FileDesc* creatEF_SPN();
FileDesc* creatEF_START_HFN();
FileDesc* creatEF_THRESHOLD();
FileDesc* creatEF_UST();

void showFileSystem(FileDesc* mf);
void showChildDFEF(FileList* fileList);
