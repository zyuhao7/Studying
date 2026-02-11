#include <iostream>
#include <vector>
#include <memory>
#include <print>
#include <ranges>
#include <algorithm>
#include <cassert>
#include "Document.h"
#include "Report.h"
#include "Note.h"

//namespace SimpleUsage
//{
//	namespace Raw
//	{
//		void Main()
//		{
//			Document* p = new Document{};
//			p->setTitle("Note");
//			p->addContent("Using  raw pointer");
//			std::cout << *p;
//			delete p;
//		}
//	}
//	namespace Smart
//	{
//		void Main()
//		{
//			std::shared_ptr<Document> p{ new Document{} };
//			std::unique_ptr<Document> up{ new Document{} };
//			p->setTitle("Note");
//			p->addContent("use shared_ptr ");
//			//delete p;
//			{
//				auto p1 = p;
//				std::cout << p1.use_count() << std::endl;
//			}
//		}
//	}
//}
//
//namespace Sharing
//{
//	namespace Raw
//	{
//		class View
//		{
//			Document* m_pDocument{};
//		public:
//			void setDocument(Document* pDoc)
//			{
//				m_pDocument = pDoc;
//			}
//			void Display() const
//			{
//				std::println("{} -> {}", m_pDocument->getTitle(), m_pDocument->getContent());
//			}
//			//~View()
//			//{
//			//	delete m_pDocument;
//			//}
//		};
//
//		void Main()
//		{
//			//View view{};
//			//Document* p = new Document{};
//			//view.setDocument(p);
//			//p->setTitle("Note");
//			//p->addContent("Useing raw pointer");
//			//view.Display();
//			//p->addContent(",this is more content");
//			//view.Display();
//			////delete p; 重复释放内存..
//
//			//Document* p1 = new Document{};
//			//view.setDocument(p1);
//			//view.Display(); // err 内存泄漏...
//			
//			//==============================================================================
//			// 共享智能指针方法 存储的原始指针 p.get()
//			//View view{};
//			//std::shared_ptr<Document> p{ new Document{} };
//			//view.setDocument(p.get());
//			//p->setTitle("Note");
//			//p->addContent("Useing raw pointer");
//			//view.Display();
//			//p->addContent(",this is more content");
//			//view.Display();
//
//			//std::shared_ptr<Document> p1{ new Document{} };
//			//view.setDocument(p1.get());
//			//view.Display(); 
//
//			//==============================================================================
//		}
//	}
//}
//
//namespace ReturnType
//{
//	namespace Raw
//	{
//		//Document* NewDocument(const std::string& title)
//		//{
//		//	if (title.empty())
//		//		return nullptr;
//		//	return new Document{ title };
//		//}
//
//		std::shared_ptr<Document> NewDocument(const std::string& title)
//		{
//			if (title.empty())
//				return nullptr;
//			return std::shared_ptr<Document>{new Document{ title }};
//		}
//
//		class View
//		{
//			std::shared_ptr<Document> m_pDocument{};
//		public:
//			void setDocument(std::shared_ptr<Document> pDoc)
//			{
//				m_pDocument = pDoc;
//			}
//			void Display() const
//			{
//				std::println("{} -> {}", m_pDocument->getTitle(), m_pDocument->getContent());
//			}
//			std::shared_ptr<Document> getDocument() const
//			{
//				return m_pDocument;
//			}
//		};
//
//		void Main()
//		{
//			//Document* p = NewDocument("Note");
//			//if (!p)
//			//{
//			//	std::println("the document could not be created");
//			//	return;
//			//}
//			//p->addContent("this is more content  ");
//			//std::cout << *p << "\n";
//			//delete p;
//
//			auto p = NewDocument("Note");
//			if (!p)
//			{
//				std::println("the document could not be created");
//				return;
//			}
//			p->addContent("this is more content  ");
//			std::cout << *p << "\n";
//			//delete p;
//
//			View* view = new View{};
//			view->setDocument(p);
//			std::cout << p.use_count() << std::endl;
//
//			view->Display();
//			auto p2 = view->getDocument();
//
//			delete view;
//			std::cout << *p2 << '\n';
//		}
//	}
//}
//
//namespace Argument
//{
//	namespace Raw
//	{
//		//void Initialize(Document* p)
//		//{
//		//	if (!p)
//		//	{
//		//		std::println("Non-existent document");
//		//		return;
//		//	}
//		//	p->setTitle("Note");
//		//	p->addContent("contains Initializing in a separate funciton");
//		//}
//		//void Serialize(Document* p)
//		//{
//		//	if (p && !p->IsEmpty())
//		//	{
//		//		std::println("Serializing document ...");
//		//		delete p;
//		//		return;
//		//	}
//		//	std::println("No content to serialize");
//		//}
//
//		//void Display(const Document* p) 
//		//{
//		//	std::println("{} -> {}", p->getTitle(), p->getContent());
//		//}	
//
//		//void Main()
//		//{
//		//	Document* p = new Document{};
//		//	Initialize(p);
//		//	Display(p);
//		//	//p->DeleteContent(); memory leak..
//		//	Serialize(p);
//		//}
//
//		
//	}
//	namespace Smart
//	{
//		void Initialize(const std::shared_ptr<Document>& p)
//		{
//			if (!p)
//			{
//				std::println("Non-existent document");
//				return;
//			}
//			p->setTitle("Note");
//			p->addContent("contains Initializing in a separate funciton");
//		}
//		void Serialize(std::shared_ptr<Document>& p)
//		{
//			if (p && !p->IsEmpty())
//			{
//				std::println("Serializing document ...");
//				p.reset();
//				p = nullptr;
//				return;
//			}
//			std::println("No content to serialize");
//		}
//
//		void Display(const std::shared_ptr<const Document>& p)
//		{
//			std::println("{} -> {}", p->getTitle(), p->getContent());
//		}
//
//		void Main()
//		{
//			std::shared_ptr<Document> p{ new Document{} };
//			Initialize(p);
//			Display(p);
//			Serialize(p);
//			if (!p)
//			{
//				std::println("Document is destroyed");
//			}
//			p.reset();
//		}
//	}
//}
//
//namespace Raw
//{
//	void Display(Document* p)
//	{
//		if(p != nullptr) 
//			std::println("[{}] contains <{}>", p->getTitle(), p->getContent());
//	}
//	//void Main()
//	//{
//	//	Document* p{ new Document{"Note"}};
//	//	p->addContent("prefer smart ptr over raw ptr");
//	//	Display(p);
//	//	delete p;
//	//}
//}
//
//namespace Example
//{
//	namespace Raw
//	{
//		class Application
//		{
//			Document* m_pDocument{};
//			unsigned char* m_pBuffer{};
//			
//		public:
//			Application()
//			{
//				m_pDocument = new Document{};
//				m_pBuffer = new unsigned char[std::numeric_limits<long long>::max()] {};
//			}
//			~Application()
//			{
//				delete m_pDocument;
//				delete[] m_pBuffer;
//			}
//		};
//
//		void Main()
//		{
//			try
//			{
//				Application app;
//				std::println("Application started with empty document");
//			}
//			catch (const std::exception& ep)
//			{
//				std::println("Exception:{}", ep.what());
//			}
//		
//		}
//	}
//
//	namespace Smart
//	{
//		class Application
//		{
//			std::shared_ptr<Document> m_pDocument{};
//			unsigned char* m_pBuffer{};
//
//		public:
//			Application()
//			{
//				m_pDocument.reset(new Document{});
//				m_pBuffer = new unsigned char[std::numeric_limits<long long>::max()] {};
//			}
//			~Application()
//			{
//				//delete m_pDocument;
//				delete[] m_pBuffer;
//			}
//		};
//
//		void Main()
//		{
//			try
//			{
//				Application app;
//				std::println("Application started with empty document");
//			}
//			catch (const std::exception& ep)
//			{
//				std::println("Exception:{}", ep.what());
//			}
//
//		}
//	}
//}
//
//namespace Raw
//{
//	void Release(const std::vector<Document*>& docs)
//	{
//		for (auto doc : docs)
//		{
//			delete doc;
//		}
//	}
//	void DisplayTitle(const std::vector<Document*> &docs)
//	{
//		for (auto doc : docs)
//		{
//			std::println("{}", doc->getTitle());
//		}
//	}
//	void Main()
//	{
//		std::vector<Document*> open_docs{};
//		open_docs.emplace_back(new Document{ "05. May sales" });
//		open_docs.emplace_back(new Document{ "01. Feb sales" });
//		open_docs.emplace_back(new Document{ "02. Jam sales" });
//		open_docs.emplace_back(new Document{ "07. Sep sales" });
//		open_docs.emplace_back(new Document{ "10. Oct sales" });
//		open_docs.emplace_back(new Document{ "02. Jam sales" });
//
//		DisplayTitle(open_docs);
//
//		std::ranges::sort(open_docs, [](const auto& lhs, const auto& rhs)
//			{
//				return lhs->getTitle() < rhs->getTitle();
//			});
//		std::println("\n Sorted");
//		DisplayTitle(open_docs);
//		const auto [first, last] = std::ranges::unique(open_docs,[](const auto& lhs, const auto& rhs)
//		{
//			return lhs->getTitle() == rhs->getTitle();
//		});
//		open_docs.erase(first, last);
//		std::println("\n Unique");
//		DisplayTitle(open_docs);
//		Release(open_docs);
//	}
//}
//
//namespace Smart
//{
//	using DocumentVector = std::vector<std::shared_ptr<Document>>;
//
//	void DisplayTitle(const DocumentVector& docs)
//	{
//		for (auto doc : docs)
//		{
//			std::println("{}", doc->getTitle());
//		}
//	}
//	void Main()
//	{
//		DocumentVector open_docs{};
//		open_docs.emplace_back(new Document{ "05. May sales" });
//		open_docs.emplace_back(new Document{ "01. Feb sales" });
//		open_docs.emplace_back(new Document{ "02. Jam sales" });
//		open_docs.emplace_back(new Document{ "07. Sep sales" });
//		open_docs.emplace_back(new Document{ "10. Oct sales" });
//		open_docs.emplace_back(new Document{ "02. Jam sales" });
//
//		DisplayTitle(open_docs);
//
//		std::ranges::sort(open_docs, [](const auto& lhs, const auto& rhs)
//			{
//				return lhs->getTitle() < rhs->getTitle();
//			});
//		std::println("\n Sorted");
//		DisplayTitle(open_docs);
//		const auto [first, last] = std::ranges::unique(open_docs, [](const auto& lhs, const auto& rhs)
//			{
//				return lhs->getTitle() == rhs->getTitle();
//			});
//		open_docs.erase(first, last);
//		std::println("\n Unique");
//		DisplayTitle(open_docs);
//	}
//}

namespace RawPtrToVector
{
	class Application
	{
		std::vector<Document*> m_Documents{};
	public:
		void List()
		{
			for (auto& d : m_Documents)
			{
				d->Display();
				std::println();
			}
		}
		void Add(Document* p)
		{
			m_Documents.emplace_back(p);
		}
		void Remove(size_t index)
		{
			auto to_delete = m_Documents[index];
			m_Documents.erase(m_Documents.begin() + index);
			delete to_delete;
		}
		Document* GetAt(size_t index)
		{
			assert(index < m_Documents.size());
			return m_Documents[index];
		}
		size_t Count() const
		{
			return m_Documents.size();
		}
		~Application()
		{
			for (auto doc : m_Documents)
				delete doc;
		}
		
	};
	void ShowProperties(const Document* p)
	{
		std::println("====== PROPERTIES =====");
		auto pDoc = const_cast<Document*>(p);

		if (auto report = dynamic_cast<Report*>(pDoc); report)
		{
			std::println("[Report:{}", pDoc->getTitle());
			std::println("[Author:{}", report->getAuthor());
		}
		else if (auto note = dynamic_cast<Note*>(pDoc); note)
		{
			std::println("[Report:{}", note->getTitle());
			std::println("[Author:{}", note->GetTags());
		}
		else
			std::println("[Document: {}", pDoc->getTitle());
	}

	void Init(Application& app)
	{
		Document* p1 = new Document{ "C++ Best Practices" };
		p1->addContent("Prefer smart pointers over raw ptrs");
		Report* rp1 = new Report{ "Expenses",  "Umar" };
		rp1->addContent("Fuel - 1200 \n");
		rp1->addContent("Food - 800");
		Note* n1 = new Note{ "Groceries" };
		n1->addContent("Milk");
		n1->addContent("Eggs");
		n1->addContent("Bread");
		n1->addContent("Apple");
		n1->AddTag("personal");
		n1->AddTag("todo");
		app.Add(p1);
		app.Add(rp1);
		app.Add(n1);
	}
	void Main()
	{
		Application app{};
		Init(app);
		app.List();
		app.Remove(1);
		ShowProperties(app.GetAt(1));
	}
}
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//SimpleUsage::Raw::Main();
	//SimpleUsage::Smart::Main();
	//Sharing::Raw::Main();

	//ReturnType::Raw::Main();
	//Argument::Raw::Main();
	//Argument::Smart::Main();

	//Raw::Main();

	//Example::Raw::Main();
	//Example::Smart::Main();

	//Raw::Main();
	//Smart::Main();

	//RawPtrToVector::Main();
}