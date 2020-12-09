#include <condition_variable>
#include <atomic>
#include<mutex>
#include <queue>
#include <memory>
#include <thread>
#include <future>
 
using namespace std;
//Класс для очереди задач
 
 
template<typename T>
class thread_save_queue
{
private:
    mutable mutex mut;
    queue<shared_ptr<T>> data_queue;
    condition_variable data_cond;
public:
    thread_save_queue()
    {
    }
 
    void wait_and_pop(T& value)
    {
        unique_lock<mutex> lk(mut);
        data_cond.wait(lk, [this]{return !data_queue.empty(); });
        value = move(*data_queue.front());
        data_queue.pop();
    }
    bool try_pop(T& value)
    {
        lock_guard<mutex> lk(mut);
        if (data_queue.empty())
            return false;
        value = move(*data_queue.front());
        data_queue.pop();
        return true;
    }
    shared_ptr<T> wait_and_pop()
    {
        unique_lock<mutex> lk(mut);
        data_cond.wait(lk, [this]{return !data_queue.empty(); });
        shared_ptr<T> res = data_queue.front();
        data_queue.pop();
        return res;
    }
    shared_ptr<T> try_pop()
    {
        lock_guard<mutex> lk(mut);
        if (data_queue.empty())
            shared_ptr<T>();
        shared_ptr<T> res = data_queue.front();
        data_queue.pop();
        return res;
    }
    void push(T new_value)
    {
        shared_ptr<T> data(
            make_shared<T>(move(new_value)));
        lock_guard<mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one();
    }
    bool empty() const
    {
        lock_guard<mutex> lk(mut);
        return data_queue.empty();
    }
};
 
 
 
//Класс присоеденения потоков
class join_threads
{
    vector<thread>& threads;
public:
    explicit join_threads(vector<thread>& threads_) :
        threads(threads_)
    {}
    ~join_threads()
    {
        for (unsigned long i = 0; i < threads.size(); ++i)
        {
            if (threads[i].joinable())
                threads[i].join();
        }
    }
 
};
 
//Обертка для  пула,что бы функция могла возвращать значения
class function_wrapper
{
    struct  impl_base
    {
        virtual void call() = 0;
        virtual ~impl_base(){}
    };
    unique_ptr<impl_base> impl;
 
    template <typename F>
    struct impl_type :impl_base
    {
        F f;
        impl_type(F&& f_) :f(move(f_)){}
        void call(){ f(); }
    };
public:
    template<typename F>
    //конструктор 
    function_wrapper(F&& f) :
        impl(new impl_type<F>(move(f)))
    {}
    void operator()(){ impl->call(); }
 
    function_wrapper() = default;
 
    function_wrapper(function_wrapper&& other) :
        impl(move(other.impl))
    {}
 
    function_wrapper& operator = (function_wrapper&& other)
    {
        impl = move(other.impl);
        return *this;
    }
    function_wrapper(const function_wrapper&) = delete;
    function_wrapper(function_wrapper&) = delete;
    function_wrapper& operator = (const function_wrapper&) = delete;
};
 
//Пул потоков реализация
class thread_pool
{
    atomic_bool done;
    thread_save_queue<function_wrapper> work_queue;
    vector<thread> threads;
    join_threads joiner;
    void worker_thread()
    {
        while (!done)
        {
            function_wrapper task;
            if (work_queue.try_pop(task))
            {
                task();
            }
            else
            {
                this_thread::yield();
            }
        }
    }
public:
    thread_pool() :joiner(threads)
    {
        done = false;
        unsigned const thread_count = thread::hardware_concurrency();
        try
        {
            for (unsigned i = 0; i < thread_count; i++)
            {
                threads.push_back(thread(&thread_pool::worker_thread, this));
            }
        }
        catch (...)
        {
            done = true;
            throw;
        }
    }
    ~thread_pool()
    {
        done = true;
    }
    template<typename FunctionType>
    future<typename result_of<FunctionType()>::type> submit(FunctionType f)
    {
            typedef typename result_of<FunctionType()>::type
                result_type;
            packaged_task<result_type()> task(move(f));
            future<result_type> res(task.get_future());
            work_queue.push(move(task));
            return res;
        }
 
};

void abc()
{
    void a = 1;
    return a;
}
 
void main()
{
    thread_pool thread;
    thread.submit(abc);
 
    system("PAUSE");
}
