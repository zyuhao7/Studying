#include "CServer.h"
int main()
{
	try {
		boost::asio::io_context  io_context;
		CServer s(io_context, 10086);
		io_context.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << endl;
	}
	boost::asio::io_context io_context;
	return 0;
}

//����α�հ�ʵ�����ӱ���
//�첽����������ȫ˫����ͨ��ģʽ�������˻�����У��������û��޸�֪�ķ�ʽ�������ݣ����ù��ĵײ������·����߼��ˡ�
//����������δ����ճ�����⣬ճ�����⽻����һ�ڴ���