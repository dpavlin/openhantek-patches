////////////////////////////////////////////////////////////////////////////////
//
//	OpenHantek
/// \file myscaledraw.h
/// \brief Declares the myScaleDraw class.
//
//	Copyright (C) 2010	Oliver Haag
//	oliver.haag@gmail.com
//
//	This program is free software: you can redistribute it and/or modify it
//	under the terms of the GNU General Public License as published by the Free
//	Software Foundation, either version 3 of the License, or (at your option)
//	any later version.
//
//	This program is distributed in the hope that it will be useful, but WITHOUT
//	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
//	FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
//	more details.
//
//	You should have received a copy of the GNU General Public License along with
//	this program.  If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////////////////////////


#ifndef MYSCALEDRAW_H
#define MYSCALEDRAW_H


#include <QtDebug>
#include <QFont>
#include <QLabel>
#include <QPainter>
#include <QPalette>

#include <qwt_scale_draw.h>


////////////////////////////////////////////////////////////////////////////////
/// \class MyScaleDraw											   myscaledraw.h
/// \brief Scale with labels drawn for both major and minor ticks.
/// These are used for the voltage knobs.
class MyScaleDraw: public QwtScaleDraw
{
	public:
		void draw(QPainter *painter, const QPalette& palette) const;
		
};


#endif
