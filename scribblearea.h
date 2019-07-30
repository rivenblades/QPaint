// ---------- scribblearea.h ----------

#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
//#include <QtPrintSupport/QPrinter>
//#include <QtPrintSupport/QPrintDialog>
class ScribbleArea : public QWidget
{
    // Declares our class as a QObject which is the base class
    // for all Qt objects
    // QObjects handle events
    Q_OBJECT

public:
    ScribbleArea(QWidget *parent = 0);

    // Handles all events
    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);

    // Has the image been modified since last save
    bool isModified() const { return modified; }
    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }


    void setMyPenWidth(int val){myPenWidth=val;}

    //Mirror axis
    bool bHAxisEnabled=false;
    bool bVAxisEnabled = false;
    QPointF hMirror_axis_start,hMirror_axis_end;
    QPointF vMirror_axis_start,vMirror_axis_end;
    void setMyPenColor(const QColor &c){myPenColor=c;}
    QColor getBackgroundColor(){return backgroundColor;}
    QColor setBackgroundColor(QColor c){ backgroundColor=c;}
public slots:

    // Events to handle
    void clearImage();
//    void print();
    void setColorFromWheel(const QColor &c){setMyPenColor(c);}

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    // Updates the scribble area where we are painting
    void paintEvent(QPaintEvent *event) override;

    // Makes sure the area we are drawing on remains
    // as large as the widget
    void resizeEvent(QResizeEvent *event) override;

private:
    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);

    // Will be marked true or false depending on if
    // we have saved after a change
    bool modified;

    // Marked true or false depending on if the user
    // is drawing
    bool scribbling;

    // Holds the current pen width & color
    int myPenWidth;
    QColor myPenColor;
    QColor backgroundColor;
    // Stores the image being drawn
    QImage image;

    // Stores the location at the current mouse event
    QPoint lastPoint;




};

#endif

// ---------- END scribblearea.h ----------
