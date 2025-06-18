#include <iostream>
#include <type_traits>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <forward>
#include <utility>  // std::move
using namespace std;

// day-2025-6-18
// 第二章-异类词典和 policy模板

// 异类词典
struct NullParameter;

namespace NSVarTypeDict
{
	// N 构造的元素数目                      TCont 容器类型         T 已经生成的类型序列
	template<size_t N, template<typename...> class TCont, typename...T>
	struct Create_ {
		using type = typename Create_<N - 1, TCont, NullParameter, T...>::type;
	};

	template<template<typename...> class TCont, typename...T>
	struct Create_<0, TCont, T...>
	{
		using type = TCont<T...>;
	};
}

template<typename...TParameters>
struct VarTypeDict
{
	template<typename...TTypes>
	struct Values
	{
		Values() = default;
		Values(std::shared_ptr<void>(&& input)[sizeof...(TTypes)])
		{
			for (size_t i = 0; i < sizeof...(TTypes); ++i)
			{
				m_tuple[i] = std::move(input[i]);
			}
		}
	public:
		// //&& 出现在函数后:成员函数的右值限定符, 表示这个成员函数 只能作用于右值对象
		template<typename TTag, typename TVal>
		auto Set(TVal&& val)&& {
			using namespace NsMultiTypeDict;
			constexpr static size_t TagPos = Tag2ID<TTag, TParameters...>;
			using rawVal = std::decay_t<TVal>;
			rawVal* tmp = new rawVal(std::forward<TVal>(val));
			m_tuple[TagPos] = std::shared_ptr<void>(tmp,
				[](void* ptr) {
					rawVal* nptr = static_cast<rawVal*>(ptr);
					delete nptr;
				});
			using new_type = NewTupleType<rawVal, TagPos, Values<>, rTypes...>;
			return new_type(std::move(m_tuple));
		}
		template<typename TTag>
		const auto& Get() const;

	private:
		std::shared_ptr<void> m_tuple[sizeof...(TTypes)];
	};

public:

	static auto Create()
	{
		using namespace NSVarTypeDict;
		using type = typename Create_<sizeof...(TParameters),
			Values>::type;
		return type{};
	}
};

 
//struct A; struct B; struct Weight;
struct FParams : public VarTypeDict<struct A, struct B, struct Weight>{};

template<typename TIn>
float fun(const TIn& in)
{
	auto a = in.template Get<A>();
	auto b = in.template Get<B>();
	auto weight = in.template Get<Weight>();
	return a * weight + b * (1 - weight);
}

int main()
{
	std::cerr << fun(FParams::Create().Set<A>(1.3f).Set<B>(2.4f).Set<Weight>(0.1f));
}


//float fun(const std::map<std::string, float>& params)
//{
//	auto a_it = params.find("a");
//	auto b_it = params.find("b");
//	auto weight_it = params.find("weight");
//
//	return (a_it->second) * (weight_it->second) +
//		(b_it->second) * (1 - (weight_it->second));
//}
//
//int main()
//{
//	std::map<std::string, float> params;
//	params["a"] = 1.3f;
//	params["b"] = 2.4f;
//	params["weight"] = 0.1f;
//	std::cerr << fun(params);
//	return 0;
//}