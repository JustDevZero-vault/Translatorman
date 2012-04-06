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

/* 
\ This is a abouttranslatorman.h file
*/

#ifndef ABOUTTRANSLATORMAN_H
#define ABOUTTRANSLATORMAN_H

#include <QDialog>

namespace Ui {
    class AboutTranslatorman;
}

class AboutTranslatorman : public QDialog
{
    Q_OBJECT

public:
    explicit AboutTranslatorman(QWidget *parent = 0);
    ~AboutTranslatorman();

    private slots:
        void on_mui_exit_clicked();

    private:
    Ui::AboutTranslatorman *ui;
};

#endif // ABOUTTRANSLATORMAN_H
