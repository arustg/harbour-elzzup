#ifndef PUZZLEPIECESHAPE_H
#define PUZZLEPIECESHAPE_H

#include <QString>
#include <QPixmap>
#include <QPainterPath>
#include <QList>
#include "helpertypes.h"

namespace Puzzle
{
namespace Creation
{

class ShapeProcessorPrivate;

class ShapeProcessor {
    ShapeProcessorPrivate *_p;

public:
    explicit ShapeProcessor(const GameDescriptor &descriptor);
    ~ShapeProcessor();

    Correction getCorrectionFor(int status);
    QPainterPath getPuzzlePieceShape(int status);
    QPainterPath getPuzzlePieceStrokeShape(int status);
    MatchMode match(int status1, int status2);
    void printPerfCounters() const;
    void resetPerfCounters();
};

void generatePuzzlePieceStatuses(unsigned rows, unsigned cols, int *statuses);

}
}

#endif // PUZZLEPIECESHAPE_H
