////////////////////////////////////////////////////////////////////////////////
//
//	OpenHantek
/// \file logknob.h
/// \brief Declares the LogKnob class.
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


#ifndef LOGKNOB_H
#define LOGKNOB_H


#include <QtDebug>
#include <QWidget>
#include <QColor>
#include <QLabel>
#include <QString>
#include <QResizeEvent>

#include <qwt_text.h>
#include <qwt_scale_engine.h>
#include <qwt_round_scale_draw.h>
#include <qwt_knob.h>

#include "helper.h"
#include "siscale.h"
#include "myscaledraw.h"


////////////////////////////////////////////////////////////////////////////////
/// \class LogKnob											  logknob.h
/// \brief Knob widget for a logarithmic knob.
/// These are used for timebase and frequencybase.
class LogKnob: public QwtKnob
{
	Q_OBJECT
	
	public:
		LogKnob(QWidget *parent = 0);
		LogKnob(Helper::Unit unit, const QString &label=0, QWidget *parent=0);
		~LogKnob();
		void setRange(double minR, double maxR);
		void setSteps(QList<double> steps);
		void setValue(double val);
		bool setUnit(Helper::Unit unit);
		QString textFromValue(double val) const;
		void setLabel(const QString &label);
		void setTickLabels(SiScale::TickLabels tl);
		
    protected:
		virtual void resizeEvent(QResizeEvent *event);
        
	private:
		void init();

		QLabel *label; ///< The knob label
		Helper::Unit unit; ///< The SI unit used for this knob
		QString unitPostfix; ///< Shown after the unit
		QList<double> steps; ///< The discrete value steps

	signals:
//		void resizeEvent(QResizeEvent *event);
	
	private slots:
};


#endif