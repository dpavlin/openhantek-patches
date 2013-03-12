////////////////////////////////////////////////////////////////////////////////
//
//	OpenHantek
/// \file siscale.cpp
/// \brief Declares the SiScale class.
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


#include <cfloat>
#include <cmath>

#include "siscale.h"
#include "helper.h"


////////////////////////////////////////////////////////////////////////////////
// class SiScale
/// \brief Initializes the LogKnob internals.
/// \param parent The parent widget.
SiScale::SiScale(Helper::Unit unit) : QwtRoundScaleDraw() {
	this->setUnit( unit );
	this->setTickLabels( SiScale::MajorTicks );
}

////////////////////////////////////////////////////////////////////////////////
/// \brief Create an SI label
/// \param value the value for which the appropriate SI suffix
/// \return String representation containing value and (prefix+)unit.
QwtText SiScale::label(double val) const {
	return Helper::valueToString(val, this->unit, 0) + this->unitPostfix;
}

/// \brief Set the unit for this label.
/// \param unit The unit shown for the value.
/// \return true on success, false on invalid unit.
bool SiScale::setUnit(Helper::Unit unit) {
	if((unsigned int) unit >= Helper::UNIT_COUNT)
		return false;	
	this->unit = unit;
	return true;
}

/// \brief Set whether to draw labels for major, minor or both ticks. 
/// \param TickLabels
void SiScale::setTickLabels(SiScale::TickLabels ticklabels) {
	this->ticklabels = ticklabels;
}

/// \brief Return the tick label setting. 
SiScale::TickLabels SiScale::tickLabels() const {
	return this->ticklabels;
}

/// \brief Override QwtScaleDraw draw method.
/// \brief Draw label for all (major and minor) ticks.
/// \param painter The painter.
/// \param palette The palette.
// http://www.qtcentre.org/threads/29039-QwtPlot-gt-axis-gt-Draw-labels-for-all-kind-of-ticks
void SiScale::draw(QPainter *painter, const QPalette& palette) const
{
	QwtRoundScaleDraw::draw(painter, palette);
	
	if (this->ticklabels == SiScale::MinorTicks
	 || this->ticklabels == SiScale::MajorAndMinorTicks)
	{
		if ( hasComponent(QwtAbstractScaleDraw::Labels) )
		{
			painter->save();
			painter->setPen(palette.color(QPalette::Text)); // ignore pen style
			painter->setFont(QFont("Verdana", 10));
			
			const QList<double> &mediumTicks = scaleDiv().ticks(QwtScaleDiv::MediumTick);
			
			for (int i = 0; i < (int)mediumTicks.count(); i++)
			{
				const double v = mediumTicks[i];
				if ( scaleDiv().contains(v) )
					drawLabel(painter, mediumTicks[i]);
			}
			
			painter->setFont(QFont("Verdana", 8));
			
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
} 
