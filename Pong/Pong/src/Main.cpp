#include <EntryPoint.h>
#include <Memory/MemoryManager.h>
#include <Memory/SharedPointer.h>
#include <Memory/UniquePointer.h>

int main()
{
	if (Soul::InitializeEngine(1280, 720, "Pong!"))
	{
		Soul::UniquePointer<int> tempInt(PARTITION(int, 1));

		LOG_DEBUG("At location %d is %d", tempInt.Raw(), *tempInt);
	}

	Soul::ShutdownEngine();
	return 0;
}