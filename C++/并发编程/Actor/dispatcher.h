#pragma once
#include "message.h"

namespace messaging
{
	//①示意关闭队列的消息
	class close_queue
	{
	};


	class dispatcher
	{
	private:
		queue* q;
		bool chained;
		//②dispatcher的实例不可复制
		dispatcher(dispatcher const&) = delete;
		dispatcher& operator=(dispatcher const&) = delete;

		//③准许TemplateDispatcher的实例访问内部数据
		template<
			typename Dispatcher,
			typename Msg,
			typename Func>
		friend class TemplateDispatcher;


		void wait_and_dispatch()
		{
			//④无限循环，等待消息并发送消息
			for (;;)
			{
				auto msg = q->wait_and_pop();
				dispatch(msg);
			}
		}

		//⑤dispatch()判别消息是否属于close_queue类型，若属于，则抛出异常
		bool dispatch(
			std::shared_ptr<message_base> const& msg)
		{
			if (dynamic_cast<wrapped_message<close_queue>*>(msg.get()))
			{
				throw close_queue();
			}
			return false;
		}
	public:
		// ⑥dispatcher是可移动的实例
		dispatcher(dispatcher&& other) :
			q(other.q), chained(other.chained)
		{
			// ⑦上游的消息分发者不会等待消息
			other.chained = true;
		}
		explicit dispatcher(queue* q_) :
			q(q_), chained(false)
		{
		}

		//⑧根据TemplateDispatcher处理某种具体类型的消息
		template<typename Message, typename Func, typename dispatcher>
		TemplateDispatcher<dispatcher, Message, Func>
			handle(Func&& f, std::string info_msg)
		{
			//std::cout << "Dispatcher  handle msg is " << info_msg << std::endl;
			return TemplateDispatcher<dispatcher, Message, Func>(
				q, this, std::forward<Func>(f), info_msg);
		}

		//⑨析构函数可能抛出异常
		~dispatcher() noexcept(false)
		{
			if (!chained)
			{
				wait_and_dispatch();
			}
		}
	};

	class sender
	{
		//①sender类中包装了消息队列的指针
		queue* q;
	public:
		//②以默认方式构造的sender类内部不含队列
		sender() :
			q(nullptr)
		{
		}

		//③根据队列指针构造sender实例
		explicit sender(queue* q_) :
			q(q_)
		{
		}
		template<typename Message>
		void send(Message const& msg)
		{
			if (q)
			{
				//④发送操作会向队列添加消息
				q->push(msg);
			}
		}
	};
	class receiver
	{
		//①receiver实例完全拥有消息队列
		queue q;
	public:
		//②receiver对象准许隐式转换为sender对象，前者拥有的队列被后者引用
		operator sender()
		{
			return sender(&q);
		}
		//③队列上的等待行为会创建一个dispatcher对象
		dispatcher wait()
		{
			return dispatcher(&q);
		}
	};




	template<typename PreviousDispatcher, typename Msg, typename Func>
	class TemplateDispatcher
	{
		std::string _msg;
		queue* q;
		PreviousDispatcher* prev;
		Func f;
		bool chained;
		TemplateDispatcher(TemplateDispatcher const&) = delete;
		TemplateDispatcher& operator=(TemplateDispatcher const&) = delete;
		template<typename Dispatcher, typename OtherMsg, typename OtherFunc>
		//①根据类模板TemplateDispatcher<>具现化而成的各种类型互为友类
		friend class TemplateDispatcher;
		void wait_and_dispatch()
		{
			for (;;)
			{
				auto msg = q->wait_and_pop();
				//②如果消息已妥善处理，则跳出无限循环
				if (dispatch(msg))
					break;
			}
		}
		bool dispatch(std::shared_ptr<message_base> const& msg)
		{
			//③查验消息型别并调用相应的处理函数
			if (wrapped_message<Msg>* wrapper =
				dynamic_cast<wrapped_message<Msg>*>(msg.get()))
			{
				f(wrapper->contents);
				return true;
			}
			else
			{
				//④衔接前一个dispatcher对象，形成连锁调用
				return prev->dispatch(msg);
			}
		}
	public:
		TemplateDispatcher(TemplateDispatcher&& other) :
			q(other.q), prev(other.prev), f(std::move(other.f)),
			chained(other.chained), _msg(other._msg)
		{
			//std::cout << "TemplateDispatcher copy construct msg is " << _msg << std::endl;
			other.chained = true;
		}
		TemplateDispatcher(queue* q_, PreviousDispatcher* prev_, Func&& f_, std::string msg) :
			q(q_), prev(prev_), f(std::forward<Func>(f_)), chained(false), _msg(msg)
		{
			//std::cout << "TemplateDispatcher  construct msg is " << _msg << std::endl;
			prev_->chained = true;
		}

		//⑤按衔接成链的方式引入更多处理函数
		template<typename OtherMsg, typename OtherFunc>
		TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc>
			handle(OtherFunc&& of, std::string  info_msg)
		{
			//std::cout << "TemplateDispatcher  handle msg is " << info_msg << std::endl;
			return TemplateDispatcher<
				TemplateDispatcher, OtherMsg, OtherFunc>(
					q, this, std::forward<OtherFunc>(of), info_msg);
		}

		//⑥该类的析构函数的异常行为描述也是noexecpt(false)
		~TemplateDispatcher() noexcept(false)
		{
			if (!chained)
			{
				wait_and_dispatch();
			}

			//std::cout << "~TemplateDispatcher  msg is " << _msg << std::endl;
		}
	};



}