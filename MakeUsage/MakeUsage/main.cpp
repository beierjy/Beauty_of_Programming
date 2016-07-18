#include <Windows.h>  
#include<stdlib.h>  
#include<tchar.h>  
#include <thread>
#include<math.h>  

const double SPLIT = 0.01;
const int COUNT = 200;
const double PI = 3.14159265;
const int INTERVAL = 300;
/*CPU��ռ������������ô�õ��ġ�ϵͳÿһ��ʱ���ˢ��CPU��ռ���ʣ�
ռ�����������ʱ����CPUæµ��ʱ�����ʱ��ı�ֵ����õ���*/
int sin_task()
{
	DWORD busySpan[COUNT]; //array of busy times  
	DWORD idleSpan[COUNT]; //array of idle times  
	int half = INTERVAL / 2;
	double radian = 0.0;
	//��ν�������һ���������ߣ�������  
	for (int i = 0; i < COUNT; ++i)
	{
		busySpan[i] = (DWORD)(half + (sin(PI * radian) * half));
		idleSpan[i] = INTERVAL - busySpan[i];
		radian += SPLIT;
	}
	DWORD startTime = 0;
	int j = 0;//�������ڵ�ֵ����
	::SetProcessAffinityMask(::GetCurrentProcess(), 0x00000002);//�������ĸ��ں���
	while (true)
	{
		j = j % COUNT;
		startTime = GetTickCount();
		while ((GetTickCount() - startTime) <= busySpan[j]);
		Sleep(idleSpan[j]);
		j++;
	}
	return 0;
}

int test()
{
	int busyTime = 9600000;
	int idleTime = busyTime*0.0000001;
	__int64 startTime = 0;
	::SetThreadAffinityMask(::GetCurrentProcess(), 0x00000001);
	while (true)
	{
		startTime = GetTickCount();
		//busy loop  
		while ((GetTickCount() - startTime) <= busyTime);
		//idle loop  
		Sleep(idleTime);
	}
	return 0;
}
int main(){
	std::thread t1(sin_task); 
	//std::thread t2(test);
	//std::thread t3(sin_task);
	//std::thread t4(sin_task);
	t1.join();
	//t2.join();
	//t3.join();
	//t4.join();
	return 0;
}