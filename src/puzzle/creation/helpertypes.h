#include <QSize>
#ifndef HELPERTYPES_H
#define HELPERTYPES_H

namespace Puzzle
{
namespace Creation
{

enum TabStatus
{
    LeftTab =      1<<0,
    LeftBlank =    1<<1,
    LeftBorder =   1<<2,

    TopTab =       1<<3,
    TopBlank =     1<<4,
    TopBorder =    1<<5,

    RightTab =     1<<6,
    RightBlank =   1<<7,
    RightBorder =  1<<8,

    BottomTab =    1<<9,
    BottomBlank =  1<<10,
    BottomBorder = 1<<11
};

enum MatchMode
{
    NoMatch = 0,
    ExactMatch,
    HorizontalFlipMatch,
    VerticalFlipMatch,
    HorizontalAndVerticalFlipMatch
};

struct Correction
{
    int sxCorrection;
    int syCorrection;
    int xCorrection;
    int yCorrection;
    int widthCorrection;
    int heightCorrection;
};

struct GameDescriptor
{
    // arustg include qsize header
    QSize viewportSize, pixmapSize, unitSize;
    int rows, cols, tabSize, tabOffset, tabFull, tabTolerance, strokeThickness, usabilityThickness;
};

class ImageProcessor;

class ShapeProcessor;

}
}

#endif // HELPERTYPES_H
