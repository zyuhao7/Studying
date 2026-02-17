#include <iostream>
#include "Document.h"
#include "AutoPointer.h"
// day-2025-2-17

void BasicUsage()
{
	//int* p = new int{ 5 };
	//*p = 10;
	//std::cout << *p << std::endl;
	//delete p;
}
void Display(const Document& doc)
{
	std::cout << "Title: " << doc.GetTitle() << std::endl;
	std::cout << "Content: " << doc.GetContent() << std::endl;
}

void Save(Document* pDoc)
{
	if (pDoc->IsEmpty())
	{
		std::cout << "Empty document cant be saved" << std::endl;
		return;
	}
	std::cout << "Document  Saved " << std::endl;
}

AutoPtr<Document> New()
{
	std::cout << "Title:";
	std::string title{};
	std::getline(std::cin, title);
	if (!title.empty())
	{
		AutoPtr<Document> pDoc{ new Document{ title } };
		return pDoc;
	}
	return AutoPtr<Document>{};
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//AutoPtr ap = new int{ 5 };



	//AutoPtr<Document> pDoc = New();
	//if (!pDoc)
	//{
	//	pDoc = new Document{};
	//}
	//pDoc->AddContent("c++ provided new/delete oeprators to manage mem");
	//Display(*pDoc);
	//Save(pDoc.get());
	

	//AutoPtr<Document> ptr = new Document{};
	//ptr.get()->AddContent("Using autoPtr");
	//std::cout << ptr.get()->GetContent() << std::endl;

	//AutoPtr<Document> pDoc{ new Document{"Memory Management"} };
	//AutoPtr<Document> docs[2];
	//docs[0] = pDoc;
	//docs[0]->AddContent("this is some content");
	//auto p1 = docs[0];
	//std::cout << p1->GetContent() << std::endl;
	//docs[0]->AddContent("end");

	AutoPtr<Document> pDoc{ new Document{"Memory Management"} };
	if (pDoc == nullptr)
	{
		// pDoc = new Document{};
	}
	pDoc->AddContent("C++");
	Save(pDoc.release());

}