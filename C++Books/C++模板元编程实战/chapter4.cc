#include <iostream>
#include <string>
#include <vector>
#include <memory>


using namespace std;
// day-2025-7-12
// 第四章-类型体系与基本数据类型

struct CategoryTags
{
	struct Scalar;		// 标量
	struct Matrix;		// 矩阵
	struct BatchScalar; // 标量列表
	struct BatchMatix;  // 矩阵列表
};

template <typename T>
constexpr bool IsMatrix = false;

template <typename T>
constexpr bool IsMatrix <const T> = IsMatrix<T>;

template <typename T>
constexpr bool IsMatrix <T&> = IsMatrix<T>;

template <typename T>
constexpr bool IsMatrix <const T&> = IsMatrix<T>;

template <typename T>
constexpr bool IsMatrix <T&&> = IsMatrix<T>;

template <typename T>
constexpr bool IsMatrix <const T&&> = IsMatrix<T>;


template <typename T>
constexpr bool IsScalar = false;

template <typename T>
constexpr bool IsScalar <const T> = IsScalar<T>;

template <typename T>
constexpr bool IsScalar <T&> = IsScalar<T>;

template <typename T>
constexpr bool IsScalar <const T&> = IsScalar<T>;

template <typename T>
constexpr bool IsScalar <T&&> = IsScalar<T>;

template <typename T>
constexpr bool IsScalar <const T&&> = IsScalar<T>;

template <typename T>
constexpr bool IsBatchScalar = false;

template <typename T>
constexpr bool IsBatchScalar <const T> = IsBatchScalar<T>;

template <typename T>
constexpr bool IsBatchScalar <T&> = IsBatchScalar<T>;

template <typename T>
constexpr bool IsBatchScalar <const T&> = IsBatchScalar<T>;

template <typename T>
constexpr bool IsBatchScalar <T&&> = IsBatchScalar<T>;

template <typename T>
constexpr bool IsBatchScalar <const T&&> = IsBatchScalar<T>;


template <typename T>
constexpr bool IsBatchMatrix = false;

template <typename T>
constexpr bool IsBatchMatrix <const T> = IsBatchMatrix<T>;

template <typename T>
constexpr bool IsBatchMatrix <T &> = IsBatchMatrix<T>;

template <typename T>
constexpr bool IsBatchMatrix <const T &> = IsBatchMatrix<T>;

template <typename T>
constexpr bool IsBatchMatrix <T &&> = IsBatchMatrix<T>;

template <typename T>
constexpr bool IsBatchMatrix <const T &&> = IsBatchMatrix<T>;

// DataCatogory 元函数
template<typename T>
struct DataCategory_
{
private:
	template<bool isScalar, bool isMatrix, bool isBatchScalar, bool isBatchMatrix,
		typename TDummy = void>
	struct helper;

	template<typename TDummy>
	struct helper<true, false, false, false, TDummy> {
		using type = CategoryTags::Scalar;
	};

	template<typename TDummy>
	struct helper<false, true, false, false, TDummy> {
		using type = CategoryTags::Matrix;
	};

	template<typename TDummy>
	struct helper<false, false, true, false, TDummy> {
		using type = CategoryTags::BatchScalar;
	};

	template<typename TDummy>
	struct helper<false, false, false, true, TDummy> {
		using type = CategoryTags::BatchMatix;
	};

public:
	using type = typename helper<IsScalar<T>, IsMatrix<T>, IsBatchScalar<T>, IsMatrix<T>>::type;

};

template<typename T>
using DataCategory = typename DataCategory_<T>::type;

struct DeviceTags
{
	struct CPU;
	struct GPU;
};

// Allocator 类模板
template<typename TDevice>
struct Allocator;

template<>
struct Allocator<DeviceTags::CPU>
{
	template<typename TElem>
	static std::shared_ptr<TElem> Allocate(size_t size)
	{
		return std::shared_ptr<TElem>(new TElem[size], [](TElem* ptr) {delete [] ptr;});
	}
};


// ContinuousMemory 模板
// 对 Allocator 分配的内存进行维护.
template<typename TElem, typename TDevice>
class ContinuousMemory
{
	static_assert(std::is_same<_Remove_const_ref_t<TElem>, TElem>::value);
	using ElementType = TElem;
public:
	explicit ContinuousMemory(size_t p_size)
		:m_mem(Allocator<TDevice>::template Allocator<ElementType>(p_size))
		,m_memStart(m_mem.get())
	{

	}
	ContinuousMemory(std::shared_ptr<ElementType> p_mem, ElementType* p_memStart)
	:m_mem(std::move(p_mem)),
	m_memStart(p_memStart)
	{

	}
	
	auto RawMemory() const { return m_memStart; }
	const std::shared_ptr<ElementType> SharePtr() const { return m_mem; }
	bool operator==(const ContinuousMemory& val) const { return m_memStart == val.m_memStart; }
	bool operator!=(const ContinuousMemory& val) const { !(operator==(val)); }
	size_t UseCount() const { return m_mem.use_count(); }

private:
	std::shared_ptr<ElementType> m_mem;
	ElementType* m_memStart;
};

// 浅拷贝与写操作检测

template<typename TData>
struct LowerAccessImpl;

template<typename TData>
auto LowerAccess(TData&& p)
{
	using RawType = _Remove_const_ref_t<TData>;
	return LowerAccessImpl<RawType>(std::forward<TData>(p));
}

//template <typename TCategory, typename TElem, typename rDevice>
//struct PrincipalDataType;
//
//template <typename TElem, typename TDevice>
//struct PrincipalDataType <CategoryTags::Matrix, TElem, TDevice>
//{
//	using type = Matrix<TElem, TDevice>;
//
//};

//其他 PrincipalDatatype 的特化
//template <typename TCategory, typename TElem, typename TDevice>
//using PrincipalDataType = typename PrincipalDataType<TCategory, TElem, TDevice>::type;

int main()
{



	return 0;
}