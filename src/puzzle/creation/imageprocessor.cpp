#include <QPainter>
#include "imageprocessor.h"
#include "../../helpers/util.h"

namespace Puzzle
{
namespace Creation
{


class ImageProcessorPrivate
{
    friend class ImageProcessor;
    QPixmap pixmap;
    GameDescriptor descriptor;
    QPixmap processImage(const QString &url, int width, int height);
};

QPixmap ImageProcessorPrivate::processImage(const QString &url, int width, int height)
{
    QPixmap pix(url);

    if (pix.isNull())
        return pix;

    // If the image is better displayed in "portrait mode", rotate it.
    if ((pix.width() < pix.height() && width >= height) || (pix.width() >= pix.height() && width < height))
    {
        pix = pix.scaledToHeight(width);
        QPixmap pix2(pix.height(), pix.width());
        QPainter p;
        p.begin(&pix2);
        p.rotate(-90);
        p.translate(- pix2.height(), 0);
        p.drawPixmap(0, 0, pix);
        p.end();
        pix = pix2;
    }

    // Scale it to our width
    if (pix.width() - 1 > width || pix.width() + 1 < width)
        pix = pix.scaledToWidth(width);

    // If still not good enough, just crop it
    if (pix.height() > height)
    {
        QPixmap pix2(width, height);
        QPainter p;
        p.begin(&pix2);
        p.drawPixmap(0, 0, pix, 0, (pix.height() - height) / 2, pix.width(), pix.height());
        p.end();
        pix = pix2;
    }

    return pix;
}

ImageProcessor::ImageProcessor(const QString &url, const QSize &viewportSize, int rows, int cols, int strokeThickness)
{
    _p = new ImageProcessorPrivate();
    _p->pixmap = _p->processImage(url, viewportSize.width(), viewportSize.height());
    _p->descriptor.rows = rows;
    _p->descriptor.cols = cols;
    _p->descriptor.viewportSize = viewportSize;
    _p->descriptor.pixmapSize = _p->pixmap.size();
    _p->descriptor.unitSize = QSize(_p->pixmap.width() / cols, _p->pixmap.height() / rows);
    _p->descriptor.tabSize = MIN(_p->descriptor.unitSize.width() / 6.0, _p->descriptor.unitSize.height() / 6.0);
    _p->descriptor.tabOffset = _p->descriptor.tabSize * 0.55;
    _p->descriptor.tabTolerance = 1;
    _p->descriptor.tabFull = _p->descriptor.tabSize + _p->descriptor.tabOffset + _p->descriptor.tabTolerance;
    _p->descriptor.strokeThickness = strokeThickness;
    _p->descriptor.usabilityThickness = MIN(80, MIN(_p->descriptor.unitSize.width(), _p->descriptor.unitSize.height()));
}

ImageProcessor::~ImageProcessor()
{
    delete _p;
}

bool ImageProcessor::isValid()
{
    return !_p->pixmap.isNull();
}

const GameDescriptor &ImageProcessor::descriptor()
{
    return _p->descriptor;
}

QPixmap ImageProcessor::drawPiece(int i, int j, const QPainterPath &shape, const Puzzle::Creation::Correction &corr)
{
    QPainter p;
    QPixmap px(_p->descriptor.unitSize.width() + corr.widthCorrection + 1,
               _p->descriptor.unitSize.height() + corr.heightCorrection + 1);
    px.fill(Qt::transparent);

    p.begin(&px);
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    p.setRenderHint(QPainter::Antialiasing);
    p.setRenderHint(QPainter::HighQualityAntialiasing);
    p.setClipping(true);
    p.setClipPath(shape);

    p.drawPixmap(_p->descriptor.tabFull + corr.xCorrection + corr.sxCorrection,
                 _p->descriptor.tabFull + corr.yCorrection + corr.syCorrection,
                 _p->pixmap,
                 i * _p->descriptor.unitSize.width() + corr.sxCorrection,
                 j * _p->descriptor.unitSize.height() + corr.syCorrection,
                 _p->descriptor.unitSize.width() * 2,
                 _p->descriptor.unitSize.height() * 2);

    p.end();
    return px;
}

QPixmap ImageProcessor::drawStroke(const QPainterPath &strokeShape, const QSize &pxSize)
{
    QPainter p;
    QPixmap stroke(pxSize.width() + _p->descriptor.strokeThickness * 2,
                   pxSize.height() + _p->descriptor.strokeThickness * 2);
    stroke.fill(Qt::transparent);
    p.begin(&stroke);
    p.setRenderHint(QPainter::SmoothPixmapTransform, true);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::HighQualityAntialiasing, true);
    p.fillPath(strokeShape, QBrush(QColor(255, 255, 255, 255)));
    p.end();

    return stroke;
}

}
}
