#include <iostream>
#include <utility>  // std::move ����ͷ�ļ�
#include <assert.h>
#include "chapter4.h"
using namespace	std;
// day-2025-7-14

//������-��������ʽģ��
// ���ʽģ�� Add
template<typename T1, typename T2>
class Add
{
public:
	Add(T1 A, T2 B)
		:m_a(std::move(A)),
		m_b(std::move(B))
	{
	}
	size_t RowNum() const
	{
		assert(m_a.RowNum() == m_b.RowNum());
		return m_a.RowNum();
	}

private:
	T1 m_a;
	T2 m_b;
};

// ����ģ�� OperElementType_ �� OperDeviceType_

template<typename TOpTag, typename TOp1, typename... TOperands>
struct OperElementType_ {
	using type = typename TOp1::ElementType;
};

template<typename TOpTag, typename TOp1, typename... TOperands>
struct OperDeviceType_ {
	using type = typename TOp1::OperDeviceType;
};



template<typename TCateCont, typename...TData>
struct Data2Cate_
{
	using type = TCateCont;
};

template<typename...TProcessed, typename TCur, typename...TRemain>
struct Data2Cate_<std::tuple<TProcessed...>, TCur, TRemain...>
{
	using tmp1 = DataCategory<TCur>;
	using tmp2 = std::tuple<TProcessed..., tmp1>;
	using type = typename Data2Cate_<tmp2, TRemain...>::type;
};

template<typename THead, typename...TRemain>
using Data2Cate = typename Data2Cate_<std::tuple<>, THead, TRemain...>::type;

template<typename TOpTag, typename THeadCate, typename...TRemainCate>
struct OperCategory_
{
	using type = THeadCate;
};

template<typename TOpTag, typename TCateContainer>
struct CateInduce_;

template<typename TOpTag, typename...TCates>
struct CateInduce_<TOpTag, std::tuple<TCates...>>
{
	using type = typename OperCategory_<TOpTag, TCates...>::type;
};

// ������ģ�� OperCateCal
template<typename TOpTag, typename THead, typename...TRemain>
using OperCateCal = typename CateInduce_<TOpTag, Data2Cate<THead, TRemain...>>::type;

// ����ģ��Ŀ��
template<typename TOpTag, typename TData>
class UnaryOp;

template<typename TOpTag, typename TData1, typename TData2>
class BinaryOp;

template<typename TOpTag, typename TData1, typename TData2, typename TData3>
class TernaryOp;

template<typename TOpTag, typename TData>
constexpr bool IsScalar<UnaryOp<TOpTag, TData>> = std::is_same<OperCateCal<TOpTag, TData>, CategoryTags::Scalar>::value;

// Sigmoid ����
// ���ڽ�һ��ʵ��ӳ�䵽(0,1)������,  S{x} = 1 / ( 1 + 1 / e^x)
// Sigmoid �����ӿ�:
template<typename TP, std::enable_if_t<OperSigmoid_<TP>::valid>* = nullptr>
auto Sigmoid(TP&& p_m)
{
	return OperSigmoid_<TP>::Eval(std::forward<TP>(p_m));
}

