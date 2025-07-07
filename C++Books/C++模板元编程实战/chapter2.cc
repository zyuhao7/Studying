#include <iostream>
#include <type_traits>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <utility>  // std::move
using namespace std;

// day-2025-6-18
// 第二章-异类词典和 policy 模板

// 异类词典
//struct NullParameter;
//
//namespace NSVarTypeDict
//{
//	// N 构造的元素数目                      TCont 容器类型         T 已经生成的类型序列
//	template<size_t N, template<typename...> class TCont, typename...T>
//	struct Create_ {
//		using type = typename Create_<N - 1, TCont, NullParameter, T...>::type;
//	};
//
//	template<template<typename...> class TCont, typename...T>
//	struct Create_<0, TCont, T...>
//	{
//		using type = TCont<T...>;
//	};
//}
//
//template<typename...TParameters>
//struct VarTypeDict
//{
//	template<typename...TTypes>
//	struct Values
//	{
//		Values() = default;
//		Values(std::shared_ptr<void>(&& input)[sizeof...(TTypes)])
//		{
//			for (size_t i = 0; i < sizeof...(TTypes); ++i)
//			{
//				m_tuple[i] = std::move(input[i]);
//			}
//		}
//	public:
//		// //&& 出现在函数后 : 成员函数的右值限定符, 表示这个成员函数 只能作用于右值对象
//		template<typename TTag, typename TVal>
//		auto Set(TVal&& val)&& {
//			using namespace NsMultiTypeDict;
//			constexpr static size_t TagPos = Tag2ID<TTag, TParameters...>;
//			using rawVal = std::decay_t<TVal>;
//			rawVal* tmp = new rawVal(std::forward<TVal>(val));
//			m_tuple[TagPos] = std::shared_ptr<void>(tmp,
//				[](void* ptr) {
//					rawVal* nptr = static_cast<rawVal*>(ptr);
//					delete nptr;
//				});
//			using new_type = NewTupleType<rawVal, TagPos, Values<>, rTypes...>;
//			return new_type(std::move(m_tuple));
//		}
//		template<typename TTag>
//		const auto& Get() const;
//
//	private:
//		std::shared_ptr<void> m_tuple[sizeof...(TTypes)];
//	};
//
//public:
//
//	static auto Create()
//	{
//		using namespace NSVarTypeDict;
//		using type = typename Create_<sizeof...(TParameters),
//			Values>::type;
//		return type{};
//	}
//};
//
// 
////struct A; struct B; struct Weight;
//struct FParams : public VarTypeDict<struct A, struct B, struct Weight>{};
//
//template<typename TIn>
//float fun(const TIn& in)
//{
//	auto a = in.template Get<A>();
//	auto b = in.template Get<B>();
//	auto weight = in.template Get<Weight>();
//	return a * weight + b * (1 - weight);
//}
//
//int main()
//{
//	std::cerr << fun(FParams::Create().Set<A>(1.3f).Set<B>(2.4f).Set<Weight>(0.1f));
//}


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

// day-2025-7-7
//  policy 模板

// 该模板包含了三个参数, 这种用于模板、控制其行为的参数称为 policy(策略).
// 与之类似的概念是 trait, trait 用于描述特性， 而 policy 用于描述行为.
//struct Add{};
//template<typename TAccuType = Add, bool doAve = false, typename ValueType = float>
//struct Accumulator{};


// ========== 策略定义 ==========
//struct AccPolicy
//{
//    struct AccuTypeCate
//    {
//        struct Add {};
//        struct Mul {};
//    };
//    using Accu = AccuTypeCate::Add;  // 默认加法
//    static constexpr bool IsAve = false;
//    using Value = float;
//};
//
//// 策略：平均值（基于加法）
//struct AveAddPolicy : AccPolicy {
//    static constexpr bool IsAve = true;
//};
//
//// 策略：乘法
//struct MulPolicy : AccPolicy {
//    using Accu = AccuTypeCate::Mul;
//};
//
//// 策略：乘法 + 平均值
//struct AveMulPolicy : AccPolicy {
//    using Accu = AccuTypeCate::Mul;
//    static constexpr bool IsAve = true;
//};
//
//// ========== 模拟策略容器和选择器 ==========
//template<typename... TPolicies>
//struct PolicyContainer
//{
//    // 简化: 不真正解析策略，使用默认
//};
//
//template<typename DefaultPolicy, typename PolicyCont>
//struct PolicySelect
//{
//    using Accu = typename DefaultPolicy::Accu;
//    static constexpr bool IsAve = DefaultPolicy::IsAve;
//    using Value = typename DefaultPolicy::Value;
//};
//
//// ========== DependencyFalse 实现 ==========
//template<typename T>
//inline constexpr bool DependencyFalse = false;
//
//// ========== 累加器主体 ==========
//template<typename Policy = AccPolicy>  // 默认用 AccPolicy
//struct Accumulotor
//{
//    using AccuType = typename Policy::Accu;
//    static constexpr bool is_ave = Policy::IsAve;
//    using ValueType = typename Policy::Value;
//
//public:
//    template<typename TIn>
//    static auto Eval(const TIn& in)
//    {
//        if constexpr (std::is_same<AccuType, typename AccPolicy::AccuTypeCate::Add>::value)
//        {
//            ValueType count = 0;
//            ValueType res = 0;
//            for (const auto& x : in)
//            {
//                res += x;
//                count++;
//            }
//            if constexpr (is_ave)
//                return res / count;
//            else
//                return res;
//        }
//        else if constexpr (std::is_same<AccuType, typename AccPolicy::AccuTypeCate::Mul>::value)
//        {
//            ValueType count = 0;
//            ValueType res = 1;
//            for (const auto& x : in)
//            {
//                res *= x;
//                count++;
//            }
//            if constexpr (is_ave)
//                return res * (1.0f / count);  // 不是几何平均
//            else
//                return res;
//        }
//        else
//        {
//            static_assert(DependencyFalse<AccuType>, "Unsupported AccuType");
//        }
//    }
//};

//int main()
//{
//    int a[] = { 1, 2, 3, 4, 5 };
//
//    // 默认求和（Add）
//    cerr << "[Default Sum]        : " << Accumulotor<>::Eval(a) << endl;  // 15
//    // 加法 + 平均值
//    cerr << "[Average (Add)]      : " << Accumulotor<AveAddPolicy>::Eval(a) << endl;  // 3
//    // 乘法
//    cerr << "[Product (Mul)]      : " << Accumulotor<MulPolicy>::Eval(a) << endl;  // 120
//    // 乘法 + 平均值
//    cerr << "[Average (Product)]  : " << Accumulotor<AveMulPolicy>::Eval(a) << endl;  // 120 * (1/5) = 24
//    // 边界测试：空容器
//    vector<float> empty;
//    cerr << "[Empty Input]        : " << Accumulotor<>::Eval(empty) << endl;  // 输出 0
//}


void func()
{
	cout << "func 1" << endl;
}
struct A
{
	void func()
	{
		cout << "func() in A" << endl;
	}
};

struct B : A
{
	void func()
	{
		cout << "func() in B" << endl;
	}
};

struct C : B
{
	void wrapper()
	{
		func();
	}

	void func()
	{
		cout << "func() in C" << endl;
	}
};
int main()
{
	C c;
	c.wrapper();
}