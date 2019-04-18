#include <iostream>
#include <memory>
#include <thread>
#include <Windows.h>

bool f1timeOut = true;
bool f2timeOut = true;
bool f3timeOut = true;

void f1(int* ptr)
{
	while (f1timeOut)
	{
		Sleep(10);
	}
	/* * * * * * * * * */
	// func() is finished on this line.
	// so sPtr's local scope is end and refer count is zero.
	Sleep(1000);
	/* * * * * * * * * */
	// Debug Assertion Failed!
	// Expression : _CrtlsValidHeapPointer(block)
	// memory disallocation is already done
	// delete ptr;
	/* * * * * * * * * */
}

void f2(std::shared_ptr<int> sPtr)
{
	printf("sPtr2 count : %d\n", sPtr.use_count());
	while (f2timeOut)
	{
		Sleep(10);
	}
	/* * * * * * * * * */
	// func() is finished on this line.
	// so sPtr's local scope is end and refer count is one.
	Sleep(100);
	/* * * * * * * * * */
	printf("sPtr2 count : %d\n", sPtr.use_count());

	/* * * * * * * * * */
	// sPtr is still on memory.
	// and count is only one.
	sPtr.reset();
	/* * * * * * * * * */
}

std::shared_ptr<int> sPtr3{ new int };

void f3(std::shared_ptr<int> sPtr)
{
	printf("sPtr3 count : %d\n", sPtr.use_count());
	while (f3timeOut)
	{
		Sleep(10);
	}
	/* * * * * * * * * */
	// func() is finished on this line.
	// so sPtr's local scope is end and refer count is one.
	Sleep(100);
	/* * * * * * * * * */
	printf("sPtr3 count : %d\n", sPtr.use_count());

	/* * * * * * * * * */
	// sPtr is still on memory.
	// but count is 2.
	// so not working.
	sPtr.reset();
	/* * * * * * * * * */
}

void func()
{
	std::shared_ptr<int> sPtr1{ new int };
	std::shared_ptr<int> sPtr2{ new int };

	std::thread t1(f1, sPtr1.get());
	std::thread t2(f2, sPtr2);
	std::thread t3(f3, sPtr3);

	t1.detach();
	t2.detach();
	t3.detach();

	f1timeOut = false;
	f2timeOut = false;
	f3timeOut = false;

}

// shared_ptr's reference counter is atomic member
// it makes overhead in multi-thread env
int main()
{
	func();

	Sleep(2000);

	printf("sPtr3 count : %d\n", sPtr3.use_count());

	// delete sPtr3.get();

	sPtr3.reset();

	printf("sPtr3 count : %d\n", sPtr3.use_count());

	system("pause");

	return 0;
}
