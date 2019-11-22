#include "layeritem.h"

LayerItem::LayerItem(QWidget *parent){
    horizontalLayout = new QHBoxLayout;
//    horizontalLayout->setSpacing(0);
//    horizontalLayout->setContentsMargins(11, 11, 11, 11);
//    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
//    horizontalLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
//    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    label = new QLabel;
    label->setObjectName(QStringLiteral("label"));
    label->setSizeIncrement(QSize(65, 25));
    label->setBaseSize(QSize(21, 17));
//    label->setStyleSheet(QStringLiteral("border-image: url(:/icons/eye_toggle_on.jpeg);"));

    horizontalLayout->addWidget(label);

    label_2 = new QLabel;
    label_2->setObjectName(QStringLiteral("label_2"));

    label->setText(QString("sa"));
    label_2->setText(QString( "Layer1"));

    horizontalLayout->addWidget(label_2);

    horizontalLayout->setStretch(0, 2);
    horizontalLayout->setStretch(1, 8);
}

void LayerItem::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int w = 65;
    int h = 25;
    painter.drawRect(QRect(pos().x(),pos().y(),w,h));
}
