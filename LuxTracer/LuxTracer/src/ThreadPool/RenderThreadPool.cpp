#include <ThreadPool/RenderThreadPool.h>

namespace lux
{
	void RenderThreadPool::Initialize()
	{
		maxThreads = std::thread::hardware_concurrency();
		if (maxThreads == 0) maxThreads = 1;
		pool.resize(maxThreads);
		for (size_t i{}; i < maxThreads; ++i)
			pool.at(i) = std::thread(&RenderThreadPool::ThreadUpdate, this);
	}

	void RenderThreadPool::Terminate()
	{
		{
			std::unique_lock<std::mutex> lock(jobMutex);
			isTerminate = true;
		}

		jobCondition.notify_all();
		for (auto& t : pool)
			t.join();
		pool.clear();
	}

	void RenderThreadPool::WaitComplete()
	{
		std::unique_lock<std::mutex> lock(jobMutex);
		idleCondition.wait(lock, [this]() { return jobs.empty() && (busyThreads == 0); });
	}

	void RenderThreadPool::QueueJob(TiledRenderData const& job)
	{
		{
			std::unique_lock<std::mutex> lock(jobMutex);
			jobs.push(job);
		}
		jobCondition.notify_one();
	}

	void RenderThreadPool::ThreadUpdate()
	{
		while (true)
		{
			TiledRenderData job;

			std::unique_lock<std::mutex> lock(jobMutex);
			jobCondition.wait(lock, [this] { return !jobs.empty() || isTerminate; });
			if (isTerminate) return;

			job = jobs.front();
			jobs.pop();
			++busyThreads;
			lock.unlock();

			//Run job
			job.Run();

			//Job completed, mark thread idle
			lock.lock();
			--busyThreads;
			idleCondition.notify_one();

			//Lock unlock upon going out of scope
		}
	}
}