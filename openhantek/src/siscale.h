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

#include <QPainter>
#include <QPalette>

#include <qwt_text.h>
#include <qwt_round_scale_draw.h>

#include "helper.h"


////////////////////////////////////////////////////////////////////////////////
/// \class SiScale
/// \brief Provide for SI unit labeled scale
/// This is used for timebase and frequencybase knobs.
class SiScale: public QwtRoundScaleDraw
{

//	Q_ENUMS ( TickLabels )
//	Q_PROPERTY( TickLabels tickLabels READ tickLabels WRITE setTickLabels )
	
	public:
		enum TickLabels
		{
			NoLabels,
			MajorTicks,
			MinorTicks,
			MajorAndMinorTicks
		};
		
		SiScale(Helper::Unit unit);

		virtual QwtText label(double val) const;
		bool setUnit(Helper::Unit unit);

		void setTickLabels( SiScale::TickLabels ticklabels);
		SiScale::TickLabels tickLabels() const;

	private:
		void draw(QPainter *painter, const QPalette& palette) const;
		
		Helper::Unit unit; ///< The SI unit used for this knob
		QString unitPostfix; ///< Shown after the unit
		SiScale::TickLabels ticklabels;

};