#include <memory>
#include <thread>
#include <Windows.h>

bool test = true;
std::unique_ptr<int> globalUniquePtr(new int);

void f2()
{
	while (test)
	{
		Sleep(10);
	}

	for (int i = 0; i < 5; i++)
	{
		Sleep(1000);
		printf("thread 2 : %d\n", *globalUniquePtr); 
	}
}

void f()
{
	std::unique_ptr<int> uPtr(new int);

	*uPtr = 100;
	printf("*uPtr = 100\n");
	test = false;
	printf("test = false\n");
	Sleep(3000);
	printf("thread 1 swap\n");
	globalUniquePtr.swap(uPtr); // 스왑 시 기존에 갖고 있던 포인터를 할당 해제?
	//globalUniquePtr.release()   // delete 된 주소를 참조하여 프로그램 비정상 종료
}

int main()
{
	std::thread thread2(f2);
	std::thread thread1(f);

	*globalUniquePtr = 50;

	int* temp = globalUniquePtr.get();

	thread1.join();
	thread2.join();

	int* temp2 = globalUniquePtr.get();

	printf("%d, %d \n", *temp, *temp2);
	
	//delete temp;  // already done ( error )
	//delete temp2; // already done ( error )

	return 0;
}