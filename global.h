#pragma once     //Ϊ�˷�ֹͷ�ļ����ظ�����

typedef struct tagVertex
{
	int row;     //��
	int col;     //��
	int info;    //��Ϣ��
}Vertex;

#define BLANK				-1
#define MAX_ROW				10	  //��ʼ����
#define MAX_COL				16	  //��ʼ����
#define MAX_VERTEX_NUM      160  //������
#define MAX_PIC_NUM         10    //ͼƬ��ɫ
#define REPEAT_NUM          16    //ÿ�ֻ�ɫͼƬ����
#define MAP_TOP             50    //��Ϸ��ͼ���Ͻ�������
#define MAP_LETF            20    //��Ϸ��ͼ���ϽǺ�����
#define PIC_HEIGHT          40    //��Ϸ��ͼ�߶�
#define PIC_WIDTH           40    //��Ϸ��ͼ���
