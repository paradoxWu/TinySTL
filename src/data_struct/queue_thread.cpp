#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

template <class value_type> class Queue
{
public:
        Queue()
        {
        }

        ~Queue()
        {
        }

        void push(value_type input)
        {
                std::lock_guard<std::mutex> lock(mutex_);
                que_.push(input);
                con_var_.notify_one();
        }

        value_type pop()
        {
                std::unique_lock<std::mutex> lk(mutex_);
                con_var_.wait(lk, [this]() { return !this->que_.empty(); });
                value_type ret = std::move(que_.front());
                que_.pop();
                return ret;
        }

        /*
         * 从队列中弹出一个元素,如果队列为空返回false
         * */
        bool try_pop(value_type &value)
        {
                std::lock_guard<std::mutex> lk(mutex_);
                if (que_.empty())
                        return false;
                value = std::move(que_.front());
                que_.pop();
                return true;
        }

        value_type front()
        {
                return que_.front();
        }

        size_t size()
        {
                return que_.size();
        }

        bool empty()
        {
                return que_.empty();
        }

private:
        std::queue<value_type> que_;
        std::mutex mutex_;
        std::condition_variable con_var_;
};