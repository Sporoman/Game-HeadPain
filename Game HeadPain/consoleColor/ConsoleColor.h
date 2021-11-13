#ifndef CONSOLECOLOR_H
#define CONSOLECOLOR_H

namespace ccolor
{
	enum class Color
	{
		black			= 0,		// Чёрный
		darkBlue		= 1,		// Тёмно-синий
		darkGreen		= 2,		// Тёмно-зелёный
		darkCyan		= 3,		// Голубой
		darkRed			= 4,		// Красный
		darkMagenta		= 5,		// Пурпурный
		brown			= 6,		// Тёмно-жёлтый (+-коричневый)
		gray			= 7,		// Светло-серый (дэфолтный)
		darkGray		= 8,		// Серый
		blue			= 9,		// Синий
		green			= 10,		// Зелёный
		cyan			= 11,		// Бирюзовый
		red				= 12,		// Алый
		magenta			= 13,		// Фиолетовый
		yellow			= 14,		// Светло-жёлтый
		white			= 15		// Белый
	};
}

#endif // !CONSOLECOLOR_H