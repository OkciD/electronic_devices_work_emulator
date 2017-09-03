#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>

class Exception
{
public:
    Exception(const QString &text): exceptionText_(text) {}
    const QString &getExceptionText() const { return exceptionText_; }

private:
    QString exceptionText_;
};

#endif // EXCEPTION_H
