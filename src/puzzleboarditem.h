#ifndef PUZZLEBOARDITEM_H
#define PUZZLEBOARDITEM_H

#include <QQuickItem>
#include <QMap>

#include "puzzle/puzzlegame.h"

class QSGTexture;
class QSGSimpleTextureNode;
class QSGTransformNode;
class QTimer;
class PuzzlePiece;
class PuzzlePiecePrimitive;

class PuzzleBoardItem : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(PuzzleGame* game READ game NOTIFY gameChanged)

    QMap<PuzzlePiece*, QSGTransformNode*> _transformNodes;
    QMap<const PuzzlePiecePrimitive*, QSGSimpleTextureNode*> _pieceTextureNodes;
    QMap<const PuzzlePiecePrimitive*, QSGSimpleTextureNode*> _strokeTextureNodes;
    QList<QSGTexture*> _textures;
    PuzzleGame *_game;
    QTimer *_autoUpdater;

    bool _clearNodes, _zOrderChanged;
    int _previousPuzzlePieces, _autoUpdateRequests;

public:
    explicit PuzzleBoardItem(QQuickItem *parent = 0);
    virtual ~PuzzleBoardItem();
    PuzzleGame *game() { return _game; }

protected:
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void touchEvent(QTouchEvent *event);

protected slots:
    void updateGame();
    void clearNodes();
    void onGameLoaded();
    void onZOrderChanged();
    void enableAutoUpdate();
    void disableAutoUpdate();

signals:
    void gameChanged();

};

#endif // PUZZLEBOARDITEM_H
