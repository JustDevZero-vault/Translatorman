/*
 * tmpreference.h
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

#ifndef TMPREFERENCE_H
#define TMPREFERENCE_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include "ui_tmpreferencebase.h"
#include "tlfunctions.h"
#include "lineedit.h"

namespace Ui {
    class TsPreference;
}

class TsPreference : public QDialog
{
    Q_OBJECT

public:
    explicit TsPreference(QWidget *parent = 0);
    ~TsPreference();

    private slots:
        void on_mui_cancel_clicked();

        void on_mui_accept_clicked();

        void on_mui_apply_clicked();

        int applychanges();

        /*void on_mui_cleanpath_clicked();*/

        void on_mui_filepath_clicked();

        void on_mui_detectwidth_clicked(bool checked);

        void on_mui_showstatusbar_clicked(bool checked);

        void on_mui_messagestatus_clicked(bool checked);

        void on_mui_autosave_clicked(bool checked);

        void on_mui_showtoolbar_clicked(bool checked);

    private:
    Ui::TsPreference *ui;
    QLineEdit *mui_pathroute;
    QString m_foldername;
    QSpinBox *mui_tabwith;
    int m_tabvalue;
    QString CAD_HOME;
    bool m_statusbar;
    QCheckBox *mui_messagestatus;
    QSpinBox *mui_minutes;
    QComboBox *mui_combotoolbar;
};

#endif // TMPREFERENCE_H
