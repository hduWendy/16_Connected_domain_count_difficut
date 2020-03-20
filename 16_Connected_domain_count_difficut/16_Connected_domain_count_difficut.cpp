// 16_Connected_domain_count_difficut.cpp : �������̨Ӧ�ó������ڵ㡣
//


#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include<algorithm>
using namespace std;
using namespace cv;
int main()
{
	//��ȡ���ص�һ��ͼƬ����ͼ���ֵ������ͨ����,��Ӳ�ҵĸ��� �����״̬��!!��!
	cv::Mat srcMat = imread("C:/Users/lenovo/Desktop/��ͼͼƬ/IMG_1989.JPG");
	//��ֵ��
	Mat g_src, labels, stats, centroids, open_src;
	threshold(srcMat, g_src, 90, 255, THRESH_BINARY_INV);
	//��ͨ������
	std::vector<cv::Mat>g_src_part(g_src.channels());//������ͨ������Ŀ��ȵ�ͼ������
	cv::split(g_src, g_src_part);//�ֽ���ͨ������Ŀ��ȵ�ͼ������
	//���ýṹԪ��+��̬����
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(12, 12), Point(-1, -1));
	morphologyEx(g_src_part[0], open_src, MORPH_OPEN, element, Point(-1, -1));
	//��ͨ����
	int num = cv::connectedComponentsWithStats(open_src, labels, stats, centroids);
	std::cout << "������" << num - 1 << std::endl;
	//����
	for (int i = 1; i <= num - 1; i++)
	{
		cv::Rect rect;
		rect.x = stats.at<int>(i, 0);
		rect.y = stats.at<int>(i, 1);
		rect.width = stats.at<int>(i, 2);
		rect.height = stats.at<int>(i, 3);
		rectangle(open_src, rect, CV_RGB(255, 255, 255), 1, 8, 0);
	}
	imshow("src", open_src);
	//�ȴ��û�����
	waitKey(0);
	return 0;
}

