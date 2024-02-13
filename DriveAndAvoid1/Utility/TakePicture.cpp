#include "TakePicture.h"
#include "InputControl.h"


TakePicture::TakePicture()
{
}

TakePicture::~TakePicture()
{
}

void TakePicture::Initialize()
{
	cap.open(0); // USB�J�����̃I�[�v��
	if (!cap.isOpened()) //�J�������N���ł��Ȃ��������̃G���[����
	{
		throw("�J�������N���ł��܂���ł���");
	}

	cascade.load("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml"); //���ʊ��񂪓����Ă���J�X�P�[�h
}

void TakePicture::Update()
{
	cap >> frame; //USB�J��������������̂P�t���[�����i�[

	//���O�̃t���[���Ŋ炪���o����Ă��Ȃ��ꍇ
	if (detection_flag == 0) {

		//���o�͈͂̓J�����f���S�̂Ƃ���
		detection_frame = frame;

		//��_�����Z�b�g
		basic_flag = 0;
		x_basic = 0;
		y_basic = 0;

	}
	else {//���O�̃t���[���Ŋ炪���o���ꂽ�ꍇ

		//��ʒ[�ɉf��ƃG���[�ɂȂ�΍�
		if (x - 50 < 1) {
			x = 51;
		}
		if (y - 50 < 1) {
			y = 51;
		}
		if (x_end + 50 > frame.cols - 1) {
			x_end = frame.cols - 51;
		}
		if (y_end + 50 > frame.rows - 1) {
			y_end = frame.rows - 51;
		}

		//���o�͈͂Ƃ��āA���O�̃t���[���̊猟�o�͈̔͂�����(�㉺���E50pixel)�傫���͈͂Ƃ���
		Rect roi(Point(x - 50, y - 50), Point(x_end + 50, y_end + 50));
		detection_frame = frame(roi);

		//���o�͈͂��s���N�g�ň͂�
		rectangle(frame, Point(x - 50, y - 50), Point(x_end + 50, y_end + 50), Scalar(200, 0, 255), 3);

		//�A�������t���O��1(2�A���ȏ��)
		basic_flag = 1;
	}

	detection_flag = 0;

	//�i�[���ꂽ�t���[���ɑ΂��ăJ�X�P�[�h�t�@�C���Ɋ�Â��Ċ�����m
	cascade.detectMultiScale(detection_frame, faces, 1.2, 5, 0, Size(20, 20));

	//������o�����ꍇ
	if (faces.size() > 0) {
		//��̌��o�t���O��1(����)�ɂ���
		detection_flag = 1;

		//����W�̍���̍��W�����߂�
		if (basic_flag == 0) {//�����m�̏ꍇ

			//�����m�̏ꍇ�͌��o���ꂽ�l�����̂܂܎g��
			x = faces[0].x;
			y = faces[0].y;

		}
		else if (basic_flag == 1) {//�A�����m�̏ꍇ

			//�A�����m�̏ꍇ�́A���o���W�ƒ��O�̊�_���g���Ċ���W�����o����
			//(x_basic - 50)�F�J�����L���v�`���S�̂̍��W���猩�����o�͈͂̍���̍��W(�s���N�g�̍���)
			//faces[0].x�F�؂�o�����t���[��(�s���N�g��)���猩����̍���̍��W(�Ԙg�̍���)

			x = (x_basic - 50) + faces[0].x;
			y = (y_basic - 50) + faces[0].y;

		}

		//����W�̉E���̍��W�����߂�
		x_end = x + faces[0].width;
		y_end = y + faces[0].height;

		//��_�����Z�o��������W�ɍX�V����
		x_basic = x;
		y_basic = y;

		rectangle(frame, Point(x, y), Point(x_end, y_end), Scalar(0, 0, 255), 3);
		//printf("(%d,%d) (%d,%d)\n", x, y, x_end, y_end);
	}

	//imshow("window", frame);//�摜��\���D

	/*int key = waitKey(1);
	
	if (key == 'e')
	{
		Rect tmp(Point(x, y), Point(x_end, y_end));
		face = frame(tmp);
		imwrite("img1.png", face);
	}*/

	
}

void TakePicture::Draw() const
{
	imshow("window", frame);//�摜��\���D
	//rectangle(frame, Point(x - 50, y - 50), Point(x_end + 50, y_end + 50), Scalar(200, 0, 255), 3);
	//rectangle(frame, Point(x, y), Point(x_end, y_end), Scalar(0, 0, 255), 3);
	//waitKey();
}

void TakePicture::Finalize()
{
}

bool TakePicture::Take()
{
	int key = waitKey(1);

	if ((InputControl::GetButtonDown(XINPUT_BUTTON_B) || key == 'e') && faces.size() > 0) {
		Rect tmp(Point(x, y), Point(x_end, y_end));
		face = frame(tmp);
		
		int handle;

		for (int i = 0; i < 128; i++)
		{
			path = "Resource/images/img" + std::to_string(i) + ".png";
			if (handle = LoadGraph(path.c_str()) == -1) {
				num = i;
				break;
			}
			DeleteGraph(handle);
		}
		resize(face, face, cv::Size(), 100.0 / face.cols, 100.0 / face.rows);
		imwrite(path, face);
		destroyAllWindows();

		return true;
	}

	return false;
}

void TakePicture::SeekNum()
{
	int handle;
	std::string path_tmp;
	for (int i = 0; i < 128; i++)
	{
		path_tmp = "Resource/images/img" + std::to_string(i) + ".png";
		handle = LoadGraph(path_tmp.c_str());
		if (handle == -1) {
			num = i - 1;
			DeleteGraph(handle);
			break;
		}
		DeleteGraph(handle);
	}
}