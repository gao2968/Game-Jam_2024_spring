#pragma once
#include<string>		//�����񑀍�
#include<sstream>		//������ϊ�
#include<fstream>		//�t�@�C������
#include "DxLib.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <vector>

using namespace cv;
using namespace std;

class TakePicture
{
private:
	static VideoCapture cap;
	static Mat frame; //USB�J�������瓾���P�t���[�����i�[����ꏊ
	static CascadeClassifier cascade; //�J�X�P�[�h���ފ�i�[�ꏊ
	//cascade.load("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml"); //���ʊ��񂪓����Ă���J�X�P�[�h
	static vector<Rect> faces; //�֊s�����i�[�ꏊ

	static Mat detection_frame;//��̌��o�͈�
	static Rect roi;
	static int detection_flag;//���O�Ɋ�����o������(0:���ĂȂ��@1:����)

	static int x;//����W�̍����x���W
	static int y;//����W�̍����y���W
	static int x_end;//����W�̉E����x���W
	static int y_end;//����W�̉E����y���W

	static int basic_flag;//�A���Ŋ�����m���Ă��邩�t���O(0:������(���߂Ă̌��m)�@1:�͂�(2�A���ȏ�̌��m))
	static int x_basic;//��_��X���W
	static int y_basic;//��_��Y���W

	//�������炨����
	static Mat face;

	static std::string path; //�摜�̍ŐV�p�X
	static int num; //�摜�������ۑ�����Ă��邩

public:
	TakePicture();
	~TakePicture();

	static void Initialize(); //����������
	static void Update(); //�X�V����
	static void Draw();//�`�揈��
	static void Finalize();//�I������

	static bool Take();
	static void SeekNum();
	static void init();

	static std::string GetPath() { return path; }
	static int GetNum() { return num; }
	
};

//#include "opencv2/opencv.hpp"
//#include "opencv2/highgui.hpp"
//#include <vector>
//
//using namespace cv;
//using namespace std;
//
//int main()
//{
//	VideoCapture cap(0); // USB�J�����̃I�[�v��
//	if (!cap.isOpened()) //�J�������N���ł��Ȃ��������̃G���[����
//	{
//		return -1;
//	}
//
//	Mat frame; //USB�J�������瓾���P�t���[�����i�[����ꏊ
//	CascadeClassifier cascade; //�J�X�P�[�h���ފ�i�[�ꏊ
//	cascade.load("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml"); //���ʊ��񂪓����Ă���J�X�P�[�h
//	vector<Rect> faces; //�֊s�����i�[�ꏊ
//
//	Mat detection_frame;//��̌��o�͈�
//	Rect roi;
//	int detection_flag = 0;//���O�Ɋ�����o������(0:���ĂȂ��@1:����)
//
//	int x = 0;//����W�̍����x���W
//	int y = 0;//����W�̍����y���W
//	int x_end = 0;//����W�̉E����x���W
//	int y_end = 0;//����W�̉E����y���W
//
//	int basic_flag = 0;//�A���Ŋ�����m���Ă��邩�t���O(0:������(���߂Ă̌��m)�@1:�͂�(2�A���ȏ�̌��m))
//	int x_basic = 0;//��_��X���W
//	int y_basic = 0;//��_��Y���W
//
//	//�������炨����
//	Mat face;
//
//	while (1)//�������[�v
//	{
//		cap >> frame; //USB�J��������������̂P�t���[�����i�[
//
//		//���O�̃t���[���Ŋ炪���o����Ă��Ȃ��ꍇ
//		if (detection_flag == 0) {
//
//			//���o�͈͂̓J�����f���S�̂Ƃ���
//			detection_frame = frame;
//
//			//��_�����Z�b�g
//			basic_flag = 0;
//			x_basic = 0;
//			y_basic = 0;
//
//		}
//		else {//���O�̃t���[���Ŋ炪���o���ꂽ�ꍇ
//
//			//���o�͈͂Ƃ��āA���O�̃t���[���̊猟�o�͈̔͂�����(�㉺���E50pixel)�傫���͈͂Ƃ���
//			Rect roi(Point(x - 50, y - 50), Point(x_end + 50, y_end + 50));
//			detection_frame = frame(roi);
//
//			//���o�͈͂��s���N�g�ň͂�
//			rectangle(frame, Point(x - 50, y - 50), Point(x_end + 50, y_end + 50), Scalar(200, 0, 255), 3);
//
//			//�A�������t���O��1(2�A���ȏ��)
//			basic_flag = 1;
//		}
//
//		detection_flag = 0;
//
//		//�i�[���ꂽ�t���[���ɑ΂��ăJ�X�P�[�h�t�@�C���Ɋ�Â��Ċ�����m
//		cascade.detectMultiScale(detection_frame, faces, 1.2, 5, 0, Size(20, 20));
//
//		//������o�����ꍇ
//		if (faces.size() > 0) {
//			//��̌��o�t���O��1(����)�ɂ���
//			detection_flag = 1;
//
//			//����W�̍���̍��W�����߂�
//			if (basic_flag == 0) {//�����m�̏ꍇ
//
//				//�����m�̏ꍇ�͌��o���ꂽ�l�����̂܂܎g��
//				x = faces[0].x;
//				y = faces[0].y;
//
//			}
//			else if (basic_flag == 1) {//�A�����m�̏ꍇ
//
//				//�A�����m�̏ꍇ�́A���o���W�ƒ��O�̊�_���g���Ċ���W�����o����
//				//(x_basic - 50)�F�J�����L���v�`���S�̂̍��W���猩�����o�͈͂̍���̍��W(�s���N�g�̍���)
//				//faces[0].x�F�؂�o�����t���[��(�s���N�g��)���猩����̍���̍��W(�Ԙg�̍���)
//
//				x = (x_basic - 50) + faces[0].x;
//				y = (y_basic - 50) + faces[0].y;
//
//			}
//
//			//����W�̉E���̍��W�����߂�
//			x_end = x + faces[0].width;
//			y_end = y + faces[0].height;
//
//			//��_�����Z�o��������W�ɍX�V����
//			x_basic = x;
//			y_basic = y;
//
//			rectangle(frame, Point(x, y), Point(x_end, y_end), Scalar(0, 0, 255), 3);
//			//printf("(%d,%d) (%d,%d)\n", x, y, x_end, y_end);
//		}
//
//		imshow("window", frame);//�摜��\���D
//
//		int key = waitKey(1);
//		if (key == 113)//q�{�^���������ꂽ�Ƃ�
//		{
//			break;//while���[�v���甲����i�I���j
//		}
//		else if (key == 'e')
//		{
//			Rect tmp(Point(x, y), Point(x_end, y_end));
//			face = frame(tmp);
//			imwrite("img1.png", face);
//		}
//	}
//	destroyAllWindows();
//	return 0;
//}