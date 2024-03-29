#include "TakePicture.h"
#include "InputControl.h"

VideoCapture TakePicture::cap;
Mat TakePicture::frame;
CascadeClassifier TakePicture::cascade;
vector<Rect> TakePicture::faces;
Mat TakePicture::detection_frame;
Rect TakePicture::roi;
int TakePicture::detection_flag = 0;
int TakePicture::x = 0, TakePicture::y = 0;
int TakePicture::x_end = 0, TakePicture::y_end = 0;
int TakePicture::basic_flag = 0;
int TakePicture::x_basic = 0, TakePicture::y_basic = 0;
Mat TakePicture::face;
std::string TakePicture::path;
int TakePicture::num;

TakePicture::TakePicture()
{
	//if (!cap.isOpened()) {
	//	cap.open(0); // USBカメラのオープン

	//	if (!cap.isOpened()) //カメラが起動できなかった時のエラー処理
	//	{
	//		//throw("カメラが起動できませんでした");
	//	}
	//}
	//cap.open(0); // USBカメラのオープン
}

TakePicture::~TakePicture()
{
}

void TakePicture::Initialize()
{
	
	if (!cap.read(frame)) {
		cap.open(0); // USBカメラのオープン

		if (!cap.read(frame)) //カメラが起動できなかった時のエラー処理
		{
			//throw("カメラが起動できませんでした");
		}
	}
	
	
	/*int a;
	while (!cap.isOpened())
	{
		a = 0;
		a = 0;
	}*/


	//cascade.load("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml"); //正面顔情報が入っているカスケード
	cascade.load("haarcascade_frontalface_alt.xml"); //正面顔情報が入っているカスケード
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

		//画面端に映るとエラーになる対策
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

		//検出範囲として、直前のフレームの顔検出の範囲より一回り(上下左右50pixel)大きい範囲とする
		Rect roi(Point(x - 50, y - 50), Point(x_end + 50, y_end + 50));
		detection_frame = frame(roi);

		//検出範囲をピンク枠で囲う
		rectangle(frame, Point(x - 50, y - 50), Point(x_end + 50, y_end + 50), Scalar(200, 0, 255), 3);

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

		rectangle(frame, Point(x, y), Point(x_end, y_end), Scalar(0, 0, 255), 3);
		//printf("(%d,%d) (%d,%d)\n", x, y, x_end, y_end);
	}

	//imshow("window", frame);//画像を表示．

	/*int key = waitKey(1);
	
	if (key == 'e')
	{
		Rect tmp(Point(x, y), Point(x_end, y_end));
		face = frame(tmp);
		imwrite("img1.png", face);
	}*/

	
}

void TakePicture::Draw()
{
	imshow("window", frame);//画像を表示．
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
		Rect tmp(Point(x + 3, y + 3), Point(x_end - 3, y_end - 3));
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
			path = "Resource/images/img" + std::to_string(num) + ".png";
			DeleteGraph(handle);
			break;
		}
		DeleteGraph(handle);
	}
}

void TakePicture::init()
{
	vector<Rect> f;
	faces = f;
}
