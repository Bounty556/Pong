#include <EntryPoint.h>
#include <Memory/MemoryManager.h>
#include <Memory/UniquePointer.h>
#include <Core/Timer.h>
#include <Structures/Stack.h>

int main()
{
	if (Soul::InitializeEngine(1280, 720, "Pong!"))
	{
		Soul::Timer timer;
		timer.Start();

		Soul::Stack<Soul::Timer> timerStack;

		Soul::Timer timer1;
		Soul::Timer timer2;
		Soul::Timer timer3;
		Soul::Timer timer4;
		Soul::Timer timer5;
		timerStack.Push(std::move(timer1));
		timerStack.Push(std::move(timer2));
		timerStack.Push(std::move(timer3));
		timerStack.Push(std::move(timer4));
		timerStack.Push(std::move(timer5));

		for (Soul::StackIterator<Soul::Timer> i = timerStack.Begin(); i != timerStack.End(); i++)
		{
			i->Start();
		}

		timer.Stop();
		LOG_DEBUG("Wowee, that took %f milliseconds!", timer.GetDeltaTime());

		int count = 1;
		for (Soul::StackIterator<Soul::Timer> i = timerStack.RBegin(); i != timerStack.REnd(); i++)
		{
			LOG_DEBUG("Timer %d had a time of %fms", count, i->GetDeltaTime());
			count++;
		}

		LOG_INFO("Time for part 2");

		for (i16 i = timerStack.Count(); timerStack.Count() > 0; i--)
		{
			Soul::Timer movedTimer = timerStack.Pop();
			LOG_DEBUG("Timer %d had a time of %fms", i, movedTimer.GetDeltaTime());
		}
	}

	Soul::ShutdownEngine();
	return 0;
}