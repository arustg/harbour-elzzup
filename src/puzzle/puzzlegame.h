#ifndef PUZZLEGAME_H
#define PUZZLEGAME_H

#include <QObject>
#include <QSize>
#include <QPoint>
#include <QPointF>
#include <QSet>

#include "../helpers/util.h"

class QTouchEvent;
class PuzzlePiece;

class PuzzleGame : public QObject
{
    Q_OBJECT
    GENPROPERTY_S(bool, _enabled, enabled, setEnabled)
    GENPROPERTY_R(bool, _allowRotation, allowRotation)
    GENPROPERTY_R(int, _strokeThickness, strokeThickness)
    GENPROPERTY_S(int, _width, width, setWidth)
    GENPROPERTY_S(int, _height, height, setHeight)
    GENPROPERTY_R(QSize, _unit, unit)
    GENPROPERTY_R(qreal, _tabSize, tabSize)
    GENPROPERTY_R(qreal, _tabOffset, tabOffset)
    GENPROPERTY_F(int, _tolerance, tolerance, setTolerance, toleranceChanged)
    Q_PROPERTY(int tolerance READ tolerance WRITE setTolerance NOTIFY toleranceChanged)
    GENPROPERTY_F(int, _rotationTolerance, rotationTolerance, setRotationTolerance, rotationToleranceChanged)
    Q_PROPERTY(int rotationTolerance READ rotationTolerance WRITE setRotationTolerance NOTIFY rotationToleranceChanged)
    GENPROPERTY_R(QSet<PuzzlePiece*>, _puzzleItems, puzzleItems)
    GENPROPERTY_F(QPointF, _rotationGuideCoordinates, rotationGuideCoordinates, setRotationGuideCoordinates, rotationGuideCoordinatesChanged)
    Q_PROPERTY(QPointF rotationGuideCoordinates READ rotationGuideCoordinates WRITE setRotationGuideCoordinates NOTIFY rotationGuideCoordinatesChanged)

    QHash<PuzzlePiece*, QPair<QPointF, int> > _restorablePositions;
    PuzzlePiece *_mouseSubject;
    bool _rotatingWithGuide;

public:
    explicit PuzzleGame(QObject *parent = 0);
    Q_INVOKABLE bool startGame(const QString &imageUrl, int rows, int cols, bool allowRotation);
    Q_INVOKABLE void startRotateWithGuide(qreal x, qreal y);
    Q_INVOKABLE void rotateWithGuide(qreal x, qreal y);
    Q_INVOKABLE void stopRotateWithGuide();
    void setNeighbours(int x, int y);
    PuzzlePiece *find(const QPoint &puzzleCoordinates);
    void removePuzzleItem(PuzzlePiece *item);

    void handleMousePress(Qt::MouseButton button, QPointF pos);
    void handleMouseRelease(Qt::MouseButton button, QPointF pos);
    void handleMouseMove(QPointF pos);
    void handleTouchEvent(QTouchEvent *event);
    
signals:
    void toleranceChanged();
    void rotationToleranceChanged();
    void rotationGuideCoordinatesChanged();

    void animationStarting();
    void animationStopped();
    void gameStarted();
    void gameWon();
    void gameAboutToBeWon();
    void loaded();
    void loadProgressChanged(int progress);
    void shuffleComplete();
    void assembleComplete();
    void restoreComplete();
    void newGameStarting();
    
public slots:
    Q_INVOKABLE void disable();
    Q_INVOKABLE void enable();
    Q_INVOKABLE void shuffle();
    Q_INVOKABLE void assemble();
    Q_INVOKABLE void restore();
    Q_INVOKABLE void deleteAllPieces();
    void emitAnimationStarting() { emit this->animationStarting(); }
    void emitAnimationStopped() { emit this->animationStopped(); }

};

#endif // PUZZLEGAME_H
