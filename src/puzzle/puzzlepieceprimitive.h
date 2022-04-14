#ifndef PUZZLEPIECEPRIMITIVE_H
#define PUZZLEPIECEPRIMITIVE_H

#include <QObject>
#include <QPointF>
#include <QPixmap>
#include <QPainterPath>

#include "../helpers/util.h"

class PuzzlePiece;

class PuzzlePiecePrimitive : public QObject
{
    Q_OBJECT
    GENPROPERTY_S(QPointF, _pixmapOffset, pixmapOffset, setPixmapOffset)
    GENPROPERTY_S(QPointF, _strokeOffset, strokeOffset, setStrokeOffset)
    GENPROPERTY_S(QPixmap, _pixmap, pixmap, setPixmap)
    GENPROPERTY_S(QPixmap, _stroke, stroke, setStroke)
    GENPROPERTY_S(QPainterPath, _realShape, realShape, setRealShape)
    GENPROPERTY_S(QPainterPath, _fakeShape, fakeShape, setFakeShape)

public:
    explicit PuzzlePiecePrimitive(PuzzlePiece *parent = 0);
    
signals:
    
public slots:
    
};

#endif // PUZZLEPIECEPRIMITIVE_H
