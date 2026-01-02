#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include "AccountManager.h"
#include "UserManager.h"

void Fun1()
{
	for (int32 i = 0; i < 1000; i++)
	{
		UserManager::Instance()->ProcessSave();
	}
}

void Fun2()
{
	for (int32 i = 0; i < 1000; i++)
	{
		AccountManager::Instance()->ProcessLogin();
	}
}

int main()
{	
	std::thread t1(Fun1);
	std::thread t2(Fun2);

	t1.join();
	t2.join();

	cout << "Jobs Done" << endl;

	// 참고
	mutex m1;
	mutex m2;

	std::lock(m1, m2);

	// adopt lock : 이미 lock된 상태니까, 나중에 소멸될때 풀어주기만 해
	lock_guard<mutex> g1(m1, std::adopt_lock);
	lock_guard<mutex> g2(m2, std::adopt_lock);
}