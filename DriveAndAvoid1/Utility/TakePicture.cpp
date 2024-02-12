#include "TakePicture.h"

TakePicture::TakePicture()
{
}

TakePicture::~TakePicture()
{
}

void TakePicture::Initialize()
{
	cap.open(0); // USBカメラのオープン
	if (!cap.isOpened()) //カメラが起動できなかった時のエラー処理
	{
		throw("カメラが起動できませんでした");
	}

	cascade.load("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml"); //正面顔情報が入っているカスケード
}

void TakePicture::Update()
{
	cap >> frame; //USBカメラが得た動画の１フレームを格納

	//直前のフレームで顔が検出されていない場合
	if (detection_flag == 0) {

		//検出範囲はカメラ映像全体とする
		detection_frame = frame;

		//基準点をリセット
		basic_flag = 0;
		x_basic = 0;
		y_basic = 0;

	}
	else {//直前のフレームで顔が検出された場合

		//検出範囲として、直前のフレームの顔検出の範囲より一回り(上下左右50pixel)大きい範囲とする
		Rect roi(Point(x - 50, y - 50), Point(x_end + 50, y_end + 50));
		detection_frame = frame(roi);

		//検出範囲をピンク枠で囲う
		//rectangle(frame, Point(x - 50, y - 50), Point(x_end + 50, y_end + 50), Scalar(200, 0, 255), 3);

		//連続検索フラグを1(2連続以上の)
		basic_flag = 1;
	}

	detection_flag = 0;

	//格納されたフレームに対してカスケードファイルに基づいて顔を検知
	cascade.detectMultiScale(detection_frame, faces, 1.2, 5, 0, Size(20, 20));

	//顔を検出した場合
	if (faces.size() > 0) {
		//顔の検出フラグを1(発見)にする
		detection_flag = 1;

		//顔座標の左上の座標を求める
		if (basic_flag == 0) {//初検知の場合

			//初検知の場合は検出された値をそのまま使う
			x = faces[0].x;
			y = faces[0].y;

		}
		else if (basic_flag == 1) {//連続検知の場合

			//連続検知の場合は、検出座標と直前の基準点を使って顔座標を検出する
			//(x_basic - 50)：カメラキャプチャ全体の座標から見た検出範囲の左上の座標(ピンク枠の左上)
			//faces[0].x：切り出したフレーム(ピンク枠内)から見た顔の左上の座標(赤枠の左上)

			x = (x_basic - 50) + faces[0].x;
			y = (y_basic - 50) + faces[0].y;

		}

		//顔座標の右下の座標を求める
		x_end = x + faces[0].width;
		y_end = y + faces[0].height;

		//基準点を今算出した顔座標に更新する
		x_basic = x;
		y_basic = y;

		//rectangle(frame, Point(x, y), Point(x_end, y_end), Scalar(0, 0, 255), 3);
		//printf("(%d,%d) (%d,%d)\n", x, y, x_end, y_end);
	}


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
	//imshow("window", frame);//画像を表示．
}

void TakePicture::Finalize()
{
}
