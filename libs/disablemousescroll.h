#ifndef DISABLEMOUSESCROLL_H
#define DISABLEMOUSESCROLL_H

#include <QObject>
#include <QEvent>

class DisableMouseScroll : public QObject
{
public:
	DisableMouseScroll(QWidget* parent = nullptr);

	virtual bool eventFilter(QObject *obj, QEvent *ev) ;
};

#endif // DISABLEMOUSESCROLL_H
