////////////////////////////////////////////////////////////////////////////////
//
//	OpenHantek
/// \file myscaledraw.cpp
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


#include "myscaledraw.h"

/// \brief Override QwtScaleDraw draw method.
/// \brief Draw label for all (major and minor) ticks.
/// \param painter The painter.
/// \param palette The palette.
void MyScaleDraw::draw(QPainter *painter, const QPalette& palette) const
{
	QwtScaleDraw::draw(painter, palette);
	
	if ( hasComponent(QwtAbstractScaleDraw::Labels) )
	{
		painter->save();
		painter->setPen(palette.color(QPalette::Text)); // ignore pen style
		painter->setFont(QFont("Verdana", 7));
		
		const QList<double> &mediumTicks = scaleDiv().ticks(QwtScaleDiv::MediumTick);
		
		for (int i = 0; i < (int)mediumTicks.count(); i++)
		{
			const double v = mediumTicks[i];
			if ( scaleDiv().contains(v) )
				drawLabel(painter, mediumTicks[i]);
		}
		
		painter->setFont(QFont("Verdana", 6));
		
		const QList<double> &minorTicks = scaleDiv().ticks(QwtScaleDiv::MinorTick);
		
		for (int i = 0; i < (int)minorTicks.count(); i++)
		{
			const double v = minorTicks[i];
			if ( scaleDiv().contains(v) )
				drawLabel(painter, minorTicks[i]);
		}
	
		painter->restore();
	}
} 

