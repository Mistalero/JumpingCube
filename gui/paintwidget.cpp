#include "paintwidget.h"

#include <QPainter>
#include <iostream>

#include <topjcdialog.h>

PaintWidget::PaintWidget(QWidget *parent) :
    QWidget(parent),image(500,500,QImage::Format_RGB32),color(Qt::black),penWidth(8)
{
    image.fill(Qt::white);
}

void PaintWidget::setImage(const QImage &img){
    image=img.copy();
    update();
}

QImage PaintWidget::getImage(){
    return image;
}

void PaintWidget::fillImage(QColor color){
    image.fill(color.value());
    update();
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPainter p(&image);
    p.setPen(color);
    p.setBrush(color);
    if(penWidth==1){
        p.drawPoint(event->pos());
    }else{
        p.drawEllipse(event->pos(),penWidth/2,penWidth/2);
    }
    // trigger repaint of widget
    update();
    tjd->paintMouseMove(event);
}


void PaintWidget::paintAt(int x, int y)
{
    QPainter p(&image);
    p.setPen(color);
    p.setBrush(color);
    if(penWidth==1){
        p.drawPoint(x,y);
    }else{
        p.drawEllipse(x,y,penWidth/2,penWidth/2);
    }
    // trigger repaint of widget
    update();
}



void PaintWidget::mouseReleaseEvent(QMouseEvent *event){
    std::cout<<"PaintWidgte::mouseReleseEvent()"<<std::endl;
    emit haveUpdate();
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawImage(0,0,image);
}
