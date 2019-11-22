#ifndef LAYERITEM_H
#define LAYERITEM_H

#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>

class LayerItem: public QWidget{
     Q_OBJECT
public:
    LayerItem(QWidget *parent=nullptr);
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // LAYERITEM_H
