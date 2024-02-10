#include <cstdio>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <cstring>
using namespace std;
using namespace cv;

void calculate_energy(Mat &ori, Mat &target, Mat &road)
{
    ori.copyTo(target);

    float a[3];
    int Min;

    for (int i = 1; i < ori.rows; i++)
    {
        if (target.at<float>(i - 1, 0) <= target.at<float>(i - 1, 1))
        {
            target.at<float>(i, 0) = ori.at<float>(i, 0) + target.at<float>(i - 1, 0);
            road.at<float>(i, 0) = 1;
        }
        else
        {
            target.at<float>(i, 0) = ori.at<float>(i, 0) + target.at<float>(i - 1, 1);
            road.at<float>(i, 0) = 2;
        }

        for (int j = 1; j < ori.cols - 1; j++)
        {
            a[0] = target.at<float>(i - 1, j - 1);
            a[1] = target.at<float>(i - 1, j);
            a[2] = target.at<float>(i - 1, j + 1);

            if (a[1] < a[0])
                Min = 1;
            else
                Min = 0;
            if (a[2] < a[Min])
                Min = 2;

            target.at<float>(i, j) = ori.at<float>(i, j) + target.at<float>(i - 1, j - 1 + Min);
            road.at<float>(i, j) = Min;
        }

        if (target.at<float>(i - 1, ori.cols - 1) <= target.at<float>(i - 1, ori.cols - 2))
        {
            target.at<float>(i, ori.cols - 1) = ori.at<float>(i, ori.cols - 1) + target.at<float>(i - 1, ori.cols - 1);
            road.at<float>(i, ori.cols - 1) = 1;
        }
        else
        {
            target.at<float>(i, ori.cols - 1) = ori.at<float>(i, ori.cols - 1) + target.at<float>(i - 1, ori.cols - 2);
            road.at<float>(i, ori.cols - 1) = 0;
        }
    }
}

void find_road(const Mat &target, const Mat &road, Mat &min)
{
    int temp = 0;

    for (int i = 1; i < target.cols; i++)
    {
        if (target.at<float>(target.rows - 1, i) < target.at<float>(target.rows - 1, temp))
            temp = i;
    }

    min.at<float>(target.rows - 1, 0) = temp;
    int temp_ = temp;
    int dir;

    for (int i = target.rows - 1; i > 0; i--)
    {
        dir = road.at<float>(i, temp_);
        if (dir == 0)
            temp_--;
        else if (dir == 2)
            temp_++;
        min.at<float>(i - 1, 0) = temp_;
    }
    return;
}

void del(Mat &ori, Mat &target, Mat &min, Mat &del_line)
{
    for (int i = 0; i < target.rows; i++)
    {
        int k = min.at<float>(i, 0);

        for (int j = 0; j < k; j++)
        {
            target.at<Vec3b>(i, j)[0] = ori.at<Vec3b>(i, j)[0];
            target.at<Vec3b>(i, j)[1] = ori.at<Vec3b>(i, j)[1];
            target.at<Vec3b>(i, j)[2] = ori.at<Vec3b>(i, j)[2];
        }

        for (int j = k; j < target.cols - 1; j++)
        {
            target.at<Vec3b>(i, j)[0] = ori.at<Vec3b>(i, j + 1)[0];
            target.at<Vec3b>(i, j)[1] = ori.at<Vec3b>(i, j + 1)[1];
            target.at<Vec3b>(i, j)[2] = ori.at<Vec3b>(i, j + 1)[2];
        }
        del_line.at<Vec3b>(i, 0)[0] = ori.at<Vec3b>(i, k)[0];
        del_line.at<Vec3b>(i, 0)[1] = ori.at<Vec3b>(i, k)[1];
        del_line.at<Vec3b>(i, 0)[2] = ori.at<Vec3b>(i, k)[2];
        // cout<<"yes"<<endl;
    }
    // cout<<"success"<<endl;
    return;
}

void operate_pic(Mat &pic, Mat &out_pic, Mat &lineOut, Mat &del_lineOut, bool sign)
{

    Mat gray_pic(pic.rows, pic.cols, CV_8U, Scalar(0));
    cvtColor(pic, gray_pic, CV_BGR2GRAY);

    Mat gradient_X(pic.rows, pic.cols, CV_32F, Scalar(0));
    Mat gradient_Y(pic.rows, pic.cols, CV_32F, Scalar(0));
    Mat gradMat(pic.rows, pic.rows, CV_32F, Scalar(0));
    Mat kernel_X = (Mat_<float>(3, 3) << 0, 0, 0, 0, 1, -1, 0, 0, 0);
    Mat kernel_Y = (Mat_<float>(3, 3) << 0, 0, 0, 0, 1, 0, 0, -1, 0);

    filter2D(gray_pic, gradient_X, gradient_X.depth(), kernel_X);
    filter2D(gray_pic, gradient_Y, gradient_Y.depth(), kernel_Y);
    add(abs(gradient_X), abs(gradient_Y), gradMat);

    Mat road(pic.rows, pic.cols, CV_32F, Scalar(0));
    Mat energy(pic.rows, pic.cols, CV_32F, Scalar(0));
    calculate_energy(gradMat, energy, road);

    Mat lineMat(pic.rows, 1, CV_32F, Scalar(0));
    find_road(energy, road, lineMat);

    Mat pic_(pic.rows, pic.cols - 1, pic.type());
    Mat del_line(pic.rows, 1, CV_8UC3);
    del(pic, pic_, lineMat, del_line);

    // if (sign)
    // imshow(" ", pic_);

    pic_.copyTo(out_pic);
    del_line.copyTo(del_lineOut);
    lineMat.copyTo(lineOut);

    return;
}
int main(int argc, char *argv)
{
    string filename = "";
    cin >> filename;

    Mat picture = imread(filename);
    // namedWindow(" ");
    // imshow(" ", pic);

    Mat tempMat;
    picture.copyTo(tempMat);

    Mat seam[picture.cols / 2];
    Mat del_lines[picture.cols / 2];
    Mat out_pic;
    Mat seams_1[tempMat.cols / 2];
    Mat del_lines_1[tempMat.cols / 2];
    Mat out_fic_f;

    for (int i = 0; i < picture.cols / 2; i++)
    {
        operate_pic(tempMat, out_pic, seam[i], del_lines[i], false);
        tempMat = out_pic;
    }
    transpose(tempMat, tempMat);
    flip(tempMat, tempMat, 1);
    for (int i = 0; i < picture.rows / 2; i++)
    {

        operate_pic(tempMat, out_fic_f, seams_1[i], del_lines_1[i], false);
        tempMat = out_fic_f;
    }
    transpose(tempMat, tempMat);
    flip(tempMat, tempMat, 0);
    out_fic_f = tempMat;

    string filenameOut = "_seam_carving.jpg";
    string outfile = "";
    int i = 0;
    for (i = 0; i < filename.length(); i++)
    {
        if (filename[i] == '.')
        {
            if (filename[1 + i] == 'j')
                break;
        }
        outfile += filename[i];
    }
    outfile += filenameOut;
    for (int i = 0; i < outfile.length(); i++)
        cout << outfile[i];
    cout << endl;
    imwrite(outfile, out_fic_f);
    return 0;
}