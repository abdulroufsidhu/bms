#include "disablemousescroll.h"

DisableMouseScroll::DisableMouseScroll(QWidget * parent) {}

bool DisableMouseScroll::eventFilter(QObject *obj, QEvent *ev) {
	if (ev->type() == QEvent::Wheel) {
		ev->ignore();
	}
}
