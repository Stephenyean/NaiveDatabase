#include "RecordManager.h"

int main()
{
	MyBitMap::initConst();   //新加的初始化
	FileManager* fm = new FileManager();
	BufPageManager* bpm = new BufPageManager(fm);
	RM_Manager* rm =new RM_Manager(fm,bpm);

	rm->CreateFile("a.txt",128);
	RM_FileHandle handle1;
	rm->OpenFile("a.txt",handle1);
	RID rid1;
	for(int i=0;i<100;i++)
		handle1.InsertRec("hello,world",rid1);

	return 0;
}