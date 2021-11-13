#ifndef CONSOLECOLOR_H
#define CONSOLECOLOR_H

namespace ccolor
{
	enum class Color
	{
		black			= 0,		// ׸����
		darkBlue		= 1,		// Ҹ���-�����
		darkGreen		= 2,		// Ҹ���-������
		darkCyan		= 3,		// �������
		darkRed			= 4,		// �������
		darkMagenta		= 5,		// ���������
		brown			= 6,		// Ҹ���-����� (+-����������)
		gray			= 7,		// ������-����� (���������)
		darkGray		= 8,		// �����
		blue			= 9,		// �����
		green			= 10,		// ������
		cyan			= 11,		// ���������
		red				= 12,		// ����
		magenta			= 13,		// ����������
		yellow			= 14,		// ������-�����
		white			= 15		// �����
	};
}

#endif // !CONSOLECOLOR_H