#include <iostream>
#include <type_traits>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <utility>  // std::move
using namespace std;

// day-2025-6-18
// �ڶ���-����ʵ�� policy ģ��

// ����ʵ�
//struct NullParameter;
//
//namespace NSVarTypeDict
//{
//	// N �����Ԫ����Ŀ                      TCont ��������         T �Ѿ����ɵ���������
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
//		// //&& �����ں����� : ��Ա��������ֵ�޶���, ��ʾ�����Ա���� ֻ����������ֵ����
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
//  policy ģ��

// ��ģ���������������, ��������ģ�塢��������Ϊ�Ĳ�����Ϊ policy(����).
// ��֮���Ƶĸ����� trait, trait �����������ԣ� �� policy ����������Ϊ.
//struct Add{};
//template<typename TAccuType = Add, bool doAve = false, typename ValueType = float>
//struct Accumulator{};


// ========== ���Զ��� ==========
//struct AccPolicy
//{
//    struct AccuTypeCate
//    {
//        struct Add {};
//        struct Mul {};
//    };
//    using Accu = AccuTypeCate::Add;  // Ĭ�ϼӷ�
//    static constexpr bool IsAve = false;
//    using Value = float;
//};
//
//// ���ԣ�ƽ��ֵ�����ڼӷ���
//struct AveAddPolicy : AccPolicy {
//    static constexpr bool IsAve = true;
//};
//
//// ���ԣ��˷�
//struct MulPolicy : AccPolicy {
//    using Accu = AccuTypeCate::Mul;
//};
//
//// ���ԣ��˷� + ƽ��ֵ
//struct AveMulPolicy : AccPolicy {
//    using Accu = AccuTypeCate::Mul;
//    static constexpr bool IsAve = true;
//};
//
//// ========== ģ�����������ѡ���� ==========
//template<typename... TPolicies>
//struct PolicyContainer
//{
//    // ��: �������������ԣ�ʹ��Ĭ��
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
//// ========== DependencyFalse ʵ�� ==========
//template<typename T>
//inline constexpr bool DependencyFalse = false;
//
//// ========== �ۼ������� ==========
//template<typename Policy = AccPolicy>  // Ĭ���� AccPolicy
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
//                return res * (1.0f / count);  // ���Ǽ���ƽ��
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
//    // Ĭ����ͣ�Add��
//    cerr << "[Default Sum]        : " << Accumulotor<>::Eval(a) << endl;  // 15
//    // �ӷ� + ƽ��ֵ
//    cerr << "[Average (Add)]      : " << Accumulotor<AveAddPolicy>::Eval(a) << endl;  // 3
//    // �˷�
//    cerr << "[Product (Mul)]      : " << Accumulotor<MulPolicy>::Eval(a) << endl;  // 120
//    // �˷� + ƽ��ֵ
//    cerr << "[Average (Product)]  : " << Accumulotor<AveMulPolicy>::Eval(a) << endl;  // 120 * (1/5) = 24
//    // �߽���ԣ�������
//    vector<float> empty;
//    cerr << "[Empty Input]        : " << Accumulotor<>::Eval(empty) << endl;  // ��� 0
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