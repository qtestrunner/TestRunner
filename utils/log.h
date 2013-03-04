#ifndef LOG_H
#define LOG_H

#include <QDebug>

//If you need to see log in gui, temporary you may run app from terminal

//TODO use different log fuctions
#ifdef QT_DEBUG
	#define DEBUG(X) qDebug() << X
	#define TRACE(X) qDebug() << X
	#define FATAL(X) qDebug() << X
#else
	#define DEBUG(X)
	#define TRACE(X)
	#define FATAL(X)
#endif

#define LOG(X) qDebug() << X

#endif // LOG_H
