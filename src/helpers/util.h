#include <QTime>
#ifndef UTIL_H
#define UTIL_H

#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))
#define MIN(x, y) ((x < y) ? (x) : (y))
#define MAX(x, y) ((x > y) ? (x) : (y))

// Simple property
#define GENPROPERTY_S(type, pname, name, settername) \
    private: type pname; \
    public: inline const type &name() const { return pname; } \
            inline void settername (const type &value) { pname = value; } \
    private:

// "Full" property with signal
#define GENPROPERTY_F(type, pname, name, settername, signalname) \
    private: type pname; \
    public: inline const type &name() const { return pname; } \
            inline void settername (const type &value) { pname = value; emit signalname (); } \
    private:

// Read-only property
#define GENPROPERTY_R(type, pname, name) \
    private: type pname; \
    public: inline const type &name() const { return pname; } \
    private:

// Property which returns a pointer
#define GENPROPERTY_PTR(type, pname, name, settername, signalname) \
    private: type pname; \
    public: inline type name() { return pname; } \
            inline void settername (type value) { pname = value; emit signalname (); } \
    private:

inline int randomInt(int low, int high)
{
    // Random number between low and high; arustg include qtime header
    return qrand() % ((high + 1) - low) + low;
}

template<typename T>
inline T myMax(const T &i, const T &j)
{
    return i > j? i : j;
}

template<typename T>
inline T myMin(const T &i, const T &j)
{
    return i < j? i : j;
}


#endif // UTIL_H
