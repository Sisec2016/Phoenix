#ifndef DZM_ACTIONCTROL_H
#define DZM_ACTIONCTROL_H

#include "GlobalTypes.h"

//0x00-0x63ͨ�ù���
//0x00-0x2f����������
#define     REGISTER                0         //ע�Ṧ��
#define     MOVE_UP                 1         //��̨����
#define     MOVE_UP_STOP            2         //��̨����ͣ
#define     MOVE_DOWN               3         //��̨����
#define     MOVE_DOWN_STOP          4         //��̨����ͣ
#define     MOVE_LEFT               5         //��̨����
#define     MOVE_LEFT_STOP          6         //��̨����ͣ
#define     MOVE_RIGHT              7         //��̨����
#define     MOVE_RIGHT_STOP         8         //��̨����ͣ
#define     MOVE_UP_LEFT            9         //��̨����
#define     MOVE_UP_LEFT_STOP       10        //��̨����ͣ
#define     MOVE_UP_RIGHT           11        //��̨����
#define     MOVE_UP_RIGHT_STOP      12        //��̨����ͣ
#define     MOVE_DOWN_LEFT          13        //��̨����
#define     MOVE_DOWN_LEFT_STOP     14        //��̨����ͣ
#define     MOVE_DOWN_RIGHT         15        //��̨����
#define     MOVE_DOWN_RIGHT_STOP    16        //��̨����ͣ
#define     SET_LEFT_BORDER         17        //������߽�
#define     SET_RIGHT_BORDER        18        //�����ұ߽�
#define     SET_UP_BORDER           19        //�����ϱ߽�
#define     SET_DOWN_BORDER         20        //�����±߽�
#define     HOR_AUTO                21        //ˮƽ�Զ�
#define     HOR_AUTO_STOP           22        //ˮƽ�Զ�ͣ
#define     SET_HOR_AUTO_BEGIN      23        //��ˮƽ�Զ���ʼ��
#define     SET_HOR_AUTO_END        24        //��ˮƽ�Զ�������
#define     SET_HOR_AUTO_SPEED      25        //����ˮƽ�Զ��ٶ�
#define     VER_AUTO                26        //��ֱ�Զ�
#define     SET_VER_AUTO_BEGIN      27        //���ô�ֱ�Զ���ʼ��
#define     SET_VER_AUTO_END        28        //���ô�ֱ�Զ�������
#define     SET_VER_AUTO_SPEED      29        //���ô�ֱ�Զ��ٶ�
#define     VER_AUTO_STOP           30        //��ֱ�Զ�ͣ

#define     ZOOM_BIG                31        //�䱶��
#define     ZOOM_BIG_STOP           32        //�䱶��ͣ
#define     ZOOM_SMALL              33        //�䱶С
#define     ZOOM_SMALL_STOP         34        //�䱶Сͣ
#define     FOCUS_FAR               35        //�۽�Զ
#define     FOCUS_FAR_STOP          36        //�۽�Զͣ
#define     FOCUS_NEAR              37        //�۽���
#define     FOCUS_NEAR_STOP         38        //�۽���ͣ
#define     IRIS_OPEN               39        //��Ȧ��
#define     IRIS_OPEN_STOP          40        //��Ȧ��ͣ
#define     IRIS_CLOSE              41        //��Ȧ��
#define     IRIS_CLOSE_STOP         42        //��Ȧ��ͣ

#define     LIGHT_ON                43        //�ƹ⿪
#define     LIGHT_OFF               44        //�ƹ��
#define     POWER_ON                45        //��Դ��
#define     POWER_OFF               46        //��Դ��
#define     RAIN_ON                 47        //��ˢ��
#define     RAIN_OFF                48        //��ˢ��
#define     TALK_ON                 49        //�Խ���
#define     TALK_OFF                50        //�Խ���
#define     DEF_ON                  51        //����
#define     DEF_OFF                 52        //����

#define     BROWSE                  53        //��ѯ
#define     ALARM_ANSWER            54        //����Ӧ��
#define     STATE_ASK               55        //�����ϴ�����״̬

//0x30-0x4f�������
#define     MOVE                    60        //������
#define     MOVE_STOP               61        //������ͣ
#define     CALL_VIEW               62        //����Ԥ�þ���
#define     SET_VIEW                63        //����Ԥ�þ���
#define     GET_VIEW_LIST           64        //���Ԥ�þ�������
#define     DELETE_VIEW             65        //ɾ��Ԥ�þ���
#define     SEQUENCE_BEGIN          66        //��ʼѲ��
#define     SEQUENCE_END            67        //ֹͣѲ��
#define     ADD_PRESET              68        //���Ѳ����
#define     DELETE_PRESET           69        //ɾ��Ѳ����
#define     GET_TRACK_SEQUENCE      70        //���Ѳ������
#define     CLEAR_SEQUENCE          71        //���Ѳ������
#define     SET_GUARD               72        //���ÿ���λ
#define     DELETE_GUARD            73        //ɾ������λ
#define     GET_GUARD_DELAY         74        //��ÿ���λ���ӳ�ʱ��
#define     GET_HOR_AUTO_SPEED      75        //���ˮƽ�Զ��ٶ�
#define     GET_VER_AUTO_SPEED      76        //��ô�ֱ�Զ��ٶ�

//ģʽ·��
#define			Pattern_Start			81				//ģʽ·����ʼ�㣨����ɨ�迪ʼ�㣩
#define			Pattern_Stop			82				//ģʽ·�������㣨����ɨ������㣩
#define			Run_Pattern 			83				//��ʼģʽ·������ʼ����ɨ�裩
#define			Stop_Pattern 			84				//ֹͣģʽ·����ֹͣ����ɨ�裩
//Ѳ��
#define			SEQUENCE_Time			85				//Ѳ����ͣ��ʱ��
#define         Set_Guard_Time          86             //����Ѳ��ʱ��

//0x64-0xc7ר�ù���
#define     SWITCH                  101        //�ֶ������л�
#define     SWITCH_MONITOR          102        //�м�
#define     SWITCH_VIDICON          103        //�е�
#define     SWITCH_ORDER            104        //˳���л�
#define     SWITCH_ORDER_STOP       105        //˳���л�ͣ
#define     SWITCH_GROUP            106        //Ⱥ���л�
#define     SWITCH_GROUP_STOP       107        //Ⱥ���л�ͣ
//��������
#define 		Guard_Link_Present			129				//������������Ԥ��λ
#define 		Guard_Link_AutoScan			130				//�������������Զ�ɨ��
#define 		Guard_Link_Cruise			131				//�������������Զ�Ѳ��
#define 		Guard_Link_Pattern			132				//������������ģʽ·��

#define     ABSOLUTEMARK     135        //3d��������
#define     OPPOSITEMARK     136        //3d�������

#define DOME_PLUS   150
#define DOME_PELCO_D  151
#define DOME_PELCO_P  152

struct Data_t
{
	int iAddress;   //�O���ַ
	int iPreset;	//�A�þ��c
	POINT point;//�Ƅӕr�������c
	unsigned char  DecBuf[256];//ݔ���Y�ϵĂ���
	int   iCount;//in and out,ݔ��ݔ���Ă���
	int   iGuardTime;//����ʱ��
	int  param[7];//3D��λ�����������飬���ϲ�������
};

#endif
