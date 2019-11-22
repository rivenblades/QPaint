
// ---------- scribblearea.cpp ----------

#include <QtWidgets>
//#if defined(QT_PRINTSUPPORT_LIB)
//#include <QtPrintSupport/qtprintsupportglobal.h>
//#if QT_CONFIG(printdialog)
//#include <QPrinter>
//#include <QPrintDialog>
//#endif
//#endif
//#include <QtPrintSupport/QPrinter>
//#include <QtPrintSupport/QPrintDialog>

#include "scribblearea.h"
#include <QtMath>
ScribbleArea::ScribbleArea(QWidget *parent)
    : QWidget(parent)
{
    // Roots the widget to the top left even if resized
    setAttribute(Qt::WA_StaticContents);

    // Set defaults for the monitored variables
    modified = false;
    scribbling = false;
    myPenWidth = 1;
    myPenColor = Qt::blue;
    backgroundColor=Qt::darkGray;

    int w = 800;
    int h = 800;
    //bHAxisEnabled = false;
    //if (bHAxisEnabled){
    hMirror_axis_start = QPointF(w/2,0);
    hMirror_axis_end = QPointF(w/2,h);
    //}
    //if(bVAxisEnabled){
    vMirror_axis_start = QPointF(0,h/2);
    vMirror_axis_end = QPointF(w,h/2);
    //}
    qDebug()<<this->width();
}

// Used to load the image and place it in the widget
bool ScribbleArea::openImage(const QString &fileName)
{
    // Holds the image
    QImage loadedImage;

    // If the image wasn't loaded leave this function
    if (!loadedImage.load(fileName))
        return false;

    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage, newSize);
    image = loadedImage;
    modified = false;
    update();
    return true;
}

// Save the current image
bool ScribbleArea::saveImage(const QString &fileName, const char *fileFormat)
{
    // Created to hold the image
    QImage visibleImage = image;
    resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName, fileFormat)) {
        modified = false;
        return true;
    } else {
        return false;
    }
}

// Used to change the pen color
void ScribbleArea::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

// Used to change the pen width
void ScribbleArea::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

// Color the image area with white
void ScribbleArea::clearImage()
{
    image.fill(backgroundColor);
    modified = true;
    update();
}

// If a mouse button is pressed check if it was the
// left button and if so store the current position
// Set that we are currently drawing
void ScribbleArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        scribbling = true;
    }
}

// When the mouse moves if the left button is clicked
// we call the drawline function which draws a line
// from the last position to the current
void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
        drawLineTo(event->pos());
}

// If the button is released we set variables to stop drawing
void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        drawLineTo(event->pos());
        scribbling = false;
    }
}

// QPainter provides functions to draw on the widget
// The QPaintEvent is sent to widgets that need to
// update themselves
void ScribbleArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);

    // Returns the rectangle that needs to be updated
    QRect dirtyRect = event->rect();

    // Draws the rectangle where the image needs to
    // be updated
    painter.drawImage(dirtyRect, image, dirtyRect);

    if(bHAxisEnabled){
        painter.drawLine(hMirror_axis_start,hMirror_axis_end);
    }
    if(bVAxisEnabled){
        painter.drawLine(vMirror_axis_start,vMirror_axis_end);
    }

    int steps = 1000;
    std::vector<QPointF> points = {QPointF(50.0f,170.0f),QPointF(150.0f,370.0f),QPointF(250.0f,350),QPointF(400.0f,320.0f),};
    QPointF oldPoint = points[0];
    for(QPointF point : curve.bezier_curve_range(steps,points)){
        painter.drawLine(oldPoint.x(), oldPoint.y(), point.x(), point.y());
        oldPoint = point;
    }

}

// Resize the image to slightly larger then the main window
// to cut down on the need to resize the image
void ScribbleArea::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void ScribbleArea::drawLineTo(const QPoint &endPoint)
{
    // Used to draw on the widget
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);

    // Set the current settings for the pen
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));

    // Draw a line from the last registered point to the current
    painter.drawLine(lastPoint, endPoint);

    // Set that the image hasn't been saved
    modified = true;

    int rad = (myPenWidth / 2) + 2;

    // Call to update the rectangular space where we drew
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));

    //MIRROR
    if(bHAxisEnabled || bVAxisEnabled){
        int xLast = lastPoint.x();int yLast=lastPoint.y();
        int xEnd = endPoint.x();int yEnd=endPoint.y();
        if(bHAxisEnabled){
            xLast = -xLast + 2*hMirror_axis_end.x();
            xEnd = -xEnd + 2*hMirror_axis_end.x();
        }
        if(bVAxisEnabled){
            yLast = -yLast + 2*vMirror_axis_end.y();
            yEnd = -yEnd + 2*vMirror_axis_end.y();
        }
        QPoint mirroredLastPoint = QPoint(xLast,yLast);
        QPoint mirroredEndPoint =  QPoint(xEnd,yEnd);
        painter.drawLine(mirroredLastPoint,mirroredEndPoint);
        //mirrored update
        // Call to update the rectangular space where we drew
        update(QRect(mirroredLastPoint, mirroredEndPoint).normalized()
                                         .adjusted(-rad, -rad, +rad, +rad));
    }
    // Update the last position where we left off drawing
    lastPoint = endPoint;
}

// When the app is resized create a new image using
// the changes made to the image
void ScribbleArea::resizeImage(QImage *image, const QSize &newSize)
{
    // Check if we need to redraw the image
    if (image->size() == newSize)
        return;

    // Create a new image to display and fill it with white
    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(backgroundColor);

    // Draw the image
    QPainter painter(&newImage);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);

    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

//// Print the image
//void ScribbleArea::print()
//{
//    // Check for print dialog availability
//#if QT_CONFIG(printdialog)

//    // Can be used to print
//    QPrinter printer(QPrinter::HighResolution);

//    // Open printer dialog and print if asked
//    QPrintDialog printDialog(&printer, this);
//    if (printDialog.exec() == QDialog::Accepted) {
//        QPainter painter(&printer);
//        QRect rect = painter.viewport();
//        QSize size = image.size();
//        size.scale(rect.size(), Qt::KeepAspectRatio);
//        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
//        painter.setWindow(image.rect());
//        painter.drawImage(0, 0, image);
//    }
//#endif // QT_CONFIG(printdialog)
//}

// ---------- END scribblearea.cpp ----------
