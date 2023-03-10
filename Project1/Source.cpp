#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

CascadeClassifier face;
vector<Rect> face_rec;
Mat art, pic, gray, cropped;
int face_x, face_y, face_w, face_h;

class Blur{
	public:
		Blur() {
			face.load("haarcascade_frontalface_default.xml");
			art = imread("aa.png");
			art.copyTo(pic);
			cvtColor(pic, gray, COLOR_BGR2GRAY);
			face.detectMultiScale(gray, face_rec);
			namedWindow("Resim", WINDOW_AUTOSIZE);
			imshow("Resim", pic);

		}
		
		static void function(int etkinlik, int x, int y, int flags, void* userdata) {
			if (etkinlik == EVENT_LBUTTONDOWN) {
				for (int i = 0; i < face_rec.size(); i++) {
					face_x = face_rec[i].x;
					face_y = face_rec[i].y;
					face_w = face_rec[i].x + face_rec[i].width;
					face_h = face_rec[i].y + face_rec[i].height;

					if ((x < face_w && x > face_x) && (y < face_h && y > face_y)){
						GaussianBlur(pic(face_rec[i]), cropped, Size(15, 15), 3);
						cropped.copyTo(pic(face_rec[i]));
						cout << "Clicked Left Button, Successfully Blurred..." << endl;
						imshow("Resim", pic);
					}
				}
			}
			if (etkinlik == EVENT_RBUTTONDOWN)
			{
				art.copyTo(pic);
				imshow("Resim", pic);
				cout << "Clicked Right Button, Successfully Removed Blur..." << endl;
			}
		}
};

int main() {
	Blur blur;
	setMouseCallback("Resim", blur.function, NULL);
	waitKey(0);
}