////////////////////////////////////////////////////////////////////////////////
//
//	OpenHantek
/// \file logknob.cpp
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

#include "logknob.h"


////////////////////////////////////////////////////////////////////////////////
/// \class LogKnob
/// \brief Initializes the LogKnob internals.
/// \param parent The parent widget.
LogKnob::LogKnob(QWidget *parent) : QwtKnob(parent) {
	this->init();
}

/// \brief Initializes the LogKnob, allowing the user to choose the unit.
/// \param unit The SI unit used for the scale.
/// \param parent The parent widget.
LogKnob::LogKnob(Helper::Unit unit, const QString &label, QWidget *parent) : QwtKnob(parent) {
	this->init();
	this->setUnit(unit);
	this->setLabel(label);
}

/// \brief Cleans up the main window.
LogKnob::~LogKnob() {
}

/// \brief Set the knob's range.
/// \param minimum value.
/// \param maxiumum value.
void LogKnob::setRange(double minR, double maxR) {
	qDebug("setRange, minR:%f maxR:%f", minR, maxR);
	QwtKnob::setScale(minR,maxR);
	QwtKnob::setRange(log10(minR), log10(maxR), 0.333333);
}

/// \brief Set the knob's discrete step values.
/// \param value list.
void LogKnob::setSteps(QList<double> steps) {
	qDebug("setSteps");
	this->steps = steps;
}

/// \brief Set the knob's value.
/// \param the current knob value.
void LogKnob::setValue(double val) {
	qDebug("setValue, val:%f", val) ;
	QwtKnob::setValue(log10(val));
}

/// \brief Get string representation of value.
/// \param val Value in base unit.
/// \return String representation containing value and (prefix+)unit.
QString LogKnob::textFromValue(double val) const {
	return Helper::valueToString(val, this->unit, -1) + this->unitPostfix;
}

/// \brief Set the unit for this knob.
/// \param unit The unit shown for the knob value.
/// \return true on success, false on invalid unit.
bool LogKnob::setUnit(Helper::Unit unit) {
	if((unsigned int) unit >= Helper::UNIT_COUNT)
		return false;	
	this->unit = unit;
//	this->scaleDraw()->setUnit(unit);
	((SiScale*) this->scaleDraw())->setUnit(unit);
	return true;
}

/// \brief Set the label for this knob.
/// \param label The label shown for this knob.
void LogKnob::setLabel(const QString &lbl) {
	qDebug() << lbl;
	label->setText(lbl);
	label->setAlignment(Qt::AlignCenter);	
}

/// \brief Draw labels for major, minor, or both ticks.
/// \param TickLabels.
void LogKnob::setTickLabels(SiScale::TickLabels tl) {
	((SiScale*) this->scaleDraw())->setTickLabels(tl);
}

/// \brief Handle resize event.
/// \param event The event pointer
void LogKnob::resizeEvent(QResizeEvent *event) {
	QwtKnob::resizeEvent(event);
	QRect qr = this->geometry();
	label->setGeometry(qr.width()/2-50, qr.height()/2+50, 100, 15);
}

/// \brief Generic initializations.
void LogKnob::init() {
	this->setScaleEngine(new QwtLog10ScaleEngine());
	this->unit = unit;
	this->setFont(QFont("Helvetica", 10, QFont::Bold));
	this->setRange( 0.5e-9, 1e3 );
	this->setValue(1.0);
	this->steps << 1.0 << 2.0 << 5.0 << 10.0;

	this->setScaleDraw(new SiScale(unit));

//	this->setTotalAngle(330);
//	this->setSymbol(QwtKnob::Dot);
	this->setScaleMaxMajor(20);
//	this->setScaleMaxMinor(3);
//	this->setMaximumWidth(100);
//	this->setMaximumHeight(100);
	this->setMinimumWidth(140);
	this->setMinimumHeight(140);
	
	QColor color(200, 200, 210);
	QPalette pal = this->palette();
	pal.setColor(QPalette::Active, QPalette::Button, color);
    this->label = new QLabel(QString::null, this);
	label->setAlignment(Qt::AlignCenter);
	label->setFont(QFont("Helvetica", 10, QFont::Bold));

	QRect qr = this->geometry();
	qDebug("LogKnob::init, x:%d, y:%d, height:%d, width:%d", qr.x(), qr.y(), qr.height(), qr.width());
}