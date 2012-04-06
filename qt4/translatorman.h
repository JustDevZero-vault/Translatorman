/*
 * translatorman.h
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



#ifndef TRANSLATORMAN_H
#define TRANSLATORMAN_H

#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QTextEdit>
#include "ui_translatormanbase.h"
#include "tlfunctions.h"

namespace Ui {
    class Translatorman;
}

class Translatorman : public QMainWindow
{
    Q_OBJECT

public:
    explicit Translatorman(QWidget *parent = 0);
    ~Translatorman();


    private slots:
        void on_actionShow_toolbar_triggered(bool checked);
        void on_actionFull_screen_triggered();
        int on_actionPreferences_triggered();
        void pantallacompleta();
        void addingTab();
        void openFile(const QString &filechosed);
        void on_actionOpen_triggered();
        void closeTab();
        void closeSelectTab(int index);
        void closeAll();
        void closeAllExcept();
        void on_actionShow_in_ngroff_triggered(bool checked);
        void on_actionShow_graphic_triggered(bool checked);
        void on_actionCut_triggered();
        void on_actionCopy_triggered();
        void on_actionPaste_triggered();
        void on_actionDelete_triggered();
        void on_actionUndo_triggered();
        void on_actionRedo_triggered();
        void on_actionAbout_Pamcli_triggered();
        void on_actionAbout_Translatorman_triggered();


        /*void copy();
        void erase();*/

    private:
    Ui::Translatorman *ui;
    QToolBar *mui_toolbar;
    QAction *m_showedToolbar;
    QAction *m_ngroff;
    QAction *m_graphic;
    QStatusBar *m_statusbar;
    QMenu *mui_file;
    QMenu *mui_edit;
    QMenu *mui_view;
    QMenu *mui_help;
    QTabWidget *mui_tabs;
    int tab_counter;
    QStringList tab_list;
};

#endif // TRANSLATORMAN_H
