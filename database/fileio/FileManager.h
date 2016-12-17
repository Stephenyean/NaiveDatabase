#ifndef FILE_MANAGER
#define FILE_MANAGER
#include <string>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "unistd.h"
//#include "../MyLinkList.h"
using namespace std;
class FileManager {
private:
	//FileTable* ftable;
	int fd[MAX_FILE_NUM];
	MyBitMap* fm;
	MyBitMap* tm;
	int _createFile(const char* name) {
		FILE* f = fopen(name, "a+");
		if (f == NULL) {
			cout << "fail" << endl;
			return -1;
		}
		fclose(f);
		return 0;
	}
	int _openFile(const char* name, int fileID) {
		int f = open(name, O_RDWR);
		if (f == -1) {
			return -1;
		}
		fd[fileID] = f;
		return 0;
	}
public:
	/*
	* FilManager���캯��
	*/
	FileManager() {
		fm = new MyBitMap(MAX_FILE_NUM, 1);
		tm = new MyBitMap(MAX_TYPE_NUM, 1);
	}
	/*
	* @������writePage
	* @����fileID:�ļ�id�����������Ѿ��򿪵��ļ�
	* @����pageID:�ļ���ҳ��
	* @����buf:�洢��Ϣ�Ļ���(4�ֽ��޷�����������)
	* @����off:ƫ����
	* ����:��buf+off��ʼ��2048�����ֽ�����(8kb��Ϣ)д��fileID��pageIDָ�����ļ�ҳ��
	* ����:�ɹ���������0
	*/
	int writePage(int fileID, int pageID, BufType buf, int off) {
		int f = fd[fileID];
		off_t offset = pageID;
		offset = (offset << PAGE_SIZE_IDX);
		off_t error = lseek(f, offset, SEEK_SET);
		if (error != offset) {
			return -1;
		}
		BufType b = buf + off;
		error = write(f, (void*)b, PAGE_SIZE);
		return 0;
	}
	/*
	* @������readPage
	* @����fileID:�ļ�id�����������Ѿ��򿪵��ļ�
	* @����pageID:�ļ�ҳ��
	* @����buf:�洢��Ϣ�Ļ���(4�ֽ��޷�����������)
	* @����off:ƫ����
	* ����:��fileID��pageIDָ�����ļ�ҳ��2048�����ֽ�����(8kb)���뵽buf+off��ʼ���ڴ���
	* ����:�ɹ���������0
	*/
	int readPage(int fileID, int pageID, BufType buf, int off) {
		//int f = fd[fID[type]];
		int f = fd[fileID];
		off_t offset = pageID;
		offset = (offset << PAGE_SIZE_IDX);
		off_t error = lseek(f, offset, SEEK_SET);
		if (error != offset) {
			return -1;
		}
		BufType b = buf + off;
		error = read(f, (void*)b, PAGE_SIZE);
		return 0;
	}
	/*
	* @������closeFile
	* @����fileID:���������Ѿ��򿪵��ļ�
	* ����:�ر��ļ�
	* ����:�����ɹ�������0
	*/
	int closeFile(int fileID) {
		fm->setBit(fileID, 1);
		int f = fd[fileID];
		close(f);
		return 0;
	}
	/*
	* @������createFile
	* @����name:�ļ���
	* ����:�½�nameָ�����ļ���
	* ����:�����ɹ�������true
	*/
	bool createFile(const char* name) {
		_createFile(name);
		return true;
	}
	/*
	* @������openFile
	* @����name:�ļ���
	* @����fileID:��������ʱ������ɹ����ļ�����ôΪ���ļ�����һ��id����¼��fileID��
	* ����:���ļ�
	* ����:����ɹ��򿪣���fileID�д洢Ϊ���ļ������id������true�����򷵻�false
	*/
	bool openFile(const char* name, int& fileID) {
		fileID = fm->findLeftOne();
		fm->setBit(fileID, 0);
		_openFile(name, fileID);
		return true;
	}
	int newType() {
		int t = tm->findLeftOne();
		tm->setBit(t, 0);
		return t;
	}
	void closeType(int typeID) {
		tm->setBit(typeID, 1);
	}
	void shutdown() {
		delete tm;
		delete fm;
	}
	~FileManager() {
		this->shutdown();
	}
};
#endif
