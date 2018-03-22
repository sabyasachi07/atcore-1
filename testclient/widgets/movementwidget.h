/* AtCore Test Client
    Copyright (C) <2018>
    Author: Chris Rizzitello - rizzitello@kde.org

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include <QComboBox>
#include <QDoubleSpinBox>
#include <QWidget>

/* Usage:
 *
 * Create a instance of the movement widget.
 */

class MovementWidget : public QWidget
{
    Q_OBJECT
public:
    MovementWidget(QWidget *parent = nullptr);

signals:
    void homeAllPressed();
    void homeXPressed();
    void homeYPressed();
    void homeZPressed();
    void absoluteMove(const QLatin1Char &axis, const double &value);
    void relativeMove(const QLatin1Char &axis, const double &value);
    void disableMotorsPressed();

private:
    QComboBox *comboMoveAxis = nullptr;
    QDoubleSpinBox *sbMoveAxis = nullptr;
};
