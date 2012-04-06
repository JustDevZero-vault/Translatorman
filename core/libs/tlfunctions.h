/*
 * template.cpp
 * Translatorman: Utility for translating or just writing, manpages into other languages.
 * Copyright (C) 2012  Daniel Ripoll <info@danielripoll.es>

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#ifndef TLFUNCTIONS_H
#define TLFUNCTIONS_H


#include <QDir>
#include <QFile>
#include <QUrl>
#include <QString>
#include <QString>
#include <QMessageBox>
#include <QDesktopServices>
#include <QTextStream>

#include <stdio.h>

#ifdef Q_OS_WIN32
	#include <qt_windows.h>
#endif

#include "tldefs.h"

void TL_EXPORT tlMsgInfo ( QString cad, QWidget *parent = 0 );
void TL_EXPORT tlMsgWarning ( QString cad, QWidget *parent = 0 );
void TL_EXPORT tlMsgError ( QString cad, QWidget *parent = 0 );


void TL_EXPORT tlWebBrowser(const QString &uri, const QString &defbrowser="");

QString TL_EXPORT tlGetEnv( const char *varName );

#ifdef Q_OS_WIN32
wchar_t* TL_EXPORT tlQStringToWCHAR (QString inString);
#endif



/// Copies a file from one location to another
bool TL_EXPORT tlCopyFile(const QString &oldName, const QString &newName);

/// Moves a file from one location to another
bool TL_EXPORT tlMoveFile(const QString &oldName, const QString &newName);

/// Deletes a file
bool TL_EXPORT tlRemove(const QString &filetoremove);

/// Open a file file
QString TL_EXPORT tlman2html( const QString &filechosed);


#endif // TLFUNCTIONS_H
