#include "Application.h"

int main()
{
	//========================================================================
	// ��Ϸ�ͻ������ӵ���Server����֤�û��������룬��֤�ɹ����·��ַ��б�
	// ÿ���ַ��б����������ơ�IP��ַ���˿�
	// AccountServer�����˺����ݿ⣬�ÿ�ֻ��һ��Account��
	//========================================================================

	Application app(6220);
	app.Run();

	return 0;
}