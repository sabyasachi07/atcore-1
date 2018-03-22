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

#include <QHBoxLayout>
#include <QPushButton>
#include <QStyle>
#include <QTime>

#include "statuswidget.h"

StatusWidget::StatusWidget(QWidget *parent) :
    QWidget(parent)
{
    //first create the item for the print Progress.
    printingProgress = new QProgressBar;

    auto newButton = new QPushButton(style()->standardIcon(QStyle::SP_BrowserStop), QString());
    connect(newButton, &QPushButton::clicked, [this] {
        emit(stopPressed());
    });

    lblTime = new QLabel(QStringLiteral("00:00:00"));
    lblTime->setAlignment(Qt::AlignHCenter);
    auto newLabel = new QLabel(QStringLiteral(" / "));
    lblTimeLeft = new QLabel(QStringLiteral("??:??:??"));
    lblTimeLeft->setAlignment(Qt::AlignHCenter);

    auto hBoxLayout = new QHBoxLayout;
    hBoxLayout->addWidget(printingProgress);
    hBoxLayout->addWidget(newButton);
    hBoxLayout->addWidget(lblTime);
    hBoxLayout->addWidget(newLabel);
    hBoxLayout->addWidget(lblTimeLeft);
    printProgressWidget = new QWidget();
    printProgressWidget->setLayout(hBoxLayout);

    //Then Create the full bar.
    newLabel = new QLabel(tr("AtCore State:"));
    lblState = new QLabel(tr("Not Connected"));
    lblSd = new QLabel();

    hBoxLayout = new QHBoxLayout;
    hBoxLayout->addWidget(newLabel);
    hBoxLayout->addWidget(lblState);
    hBoxLayout->addSpacerItem(new QSpacerItem(10, 20, QSizePolicy::Fixed));
    hBoxLayout->addWidget(lblSd);
    hBoxLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding));
    hBoxLayout->addWidget(printProgressWidget);

    setLayout(hBoxLayout);

    printTime = new QTime();
    printTimer = new QTimer();
    printTimer->setInterval(1000);
    printTimer->setSingleShot(false);
    connect(printTimer, &QTimer::timeout, this, &StatusWidget::updatePrintTime);
}

void StatusWidget::setSD(bool hasSd)
{
    QString labelText = hasSd ? tr("SD") : QString();
    lblSd->setText(labelText);
}
void StatusWidget::setState(const QString &state)
{
    lblState->setText(state);
}

void StatusWidget::showPrintArea(bool visible)
{
    printProgressWidget->setVisible(visible);
    if (visible) {
        printTime->start();
        printTimer->start();
    } else {
        printTimer->stop();
    }
}

void StatusWidget::updatePrintTime()
{
    QTime temp(0, 0, 0);
    lblTime->setText(temp.addMSecs(printTime->elapsed()).toString(QStringLiteral("hh:mm:ss")));
}

void StatusWidget::updatePrintProgress(const float &progress)
{
    printingProgress->setValue(progress);
    if (progress > 0) {
        QTime temp(0, 0, 0);
        lblTimeLeft->setText(temp.addMSecs((100 - progress) * (printTime->elapsed() / progress)).toString(QStringLiteral("hh:mm:ss")));
    } else {
        lblTimeLeft->setText(QStringLiteral("??:??:??"));
    }
}
