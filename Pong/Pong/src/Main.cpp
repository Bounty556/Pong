#include <EntryPoint.h>
#include <Memory/MemoryManager.h>
#include <Memory/UniquePointer.h>
#include <Core/Timer.h>

int main()
{
	if (Soul::InitializeEngine(1280, 720, "Pong!"))
	{
		Soul::Timer timer;
		timer.Start();

		Soul::MemoryManager::DrawMemory();

		Soul::UniquePointer<int> tempInt(PARTITION(int, 1));

		Soul::MemoryManager::DrawMemory();

		LOG_DEBUG("At location %d is %d", tempInt.Raw(), *tempInt);

		timer.Stop();

		LOG_DEBUG("Wowee, that took %f milliseconds!", timer.GetDeltaTime());
	}
	Soul::MemoryManager::DrawMemory();

	Soul::ShutdownEngine();
	return 0;
}