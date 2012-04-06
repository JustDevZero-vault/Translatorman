/*
 * translatorman.cpp
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



#include "translatorman.h"
#include "tmpreference.h"
#include "abouttranslatorman.h"

#include <QTextStream>
#include <QFileInfo>

#ifndef Q_OS_WIN32
    /// Detecting enviroment variables
    QString userFolder = getenv ( "HOME" );
#else
    QString userFolder = tlGetEnv("UserProfile");
#endif // Q_OS_WIN32


Translatorman::Translatorman(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Translatorman)
{

    /// Init the class
    ui->setupUi(this);

    // Declaration of menu pointers.
    mui_toolbar = ui->menuToolbar;
    mui_file = ui->menuFile;
    mui_edit = ui->menuEdit;
    mui_view = ui->menuView;
    mui_help = ui->menuHelp;
    mui_tabs = ui->mui_tabWidget;
    m_showedToolbar = ui->actionShow_toolbar;
    m_ngroff = ui->actionShow_in_ngroff;
    m_graphic = ui->actionShow_graphic;
    m_statusbar = ui->statusbar;

    // Declaration of actions
    mui_tabs->setTabsClosable(true);
    m_showedToolbar->setChecked ( true );
    m_ngroff->setChecked(true);
    m_graphic->setChecked(false);


    // Collection of connects.
    connect(ui->actionQuit,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->actionNew,SIGNAL(triggered()),this,SLOT(addingTab()));
    connect(ui->actionClose,SIGNAL(triggered()),this,SLOT(closeTab()));
    connect(mui_tabs,SIGNAL(tabCloseRequested(int)),this,SLOT(closeSelectTab(int)));
    connect(ui->actionClose_all,SIGNAL(triggered()),this,SLOT(closeAll()));
    connect(ui->actionCloseall_except,SIGNAL(triggered()),this,SLOT(closeAllExcept()));



    // Declaration of variables
    tab_counter = 0;
    tab_list;

}

Translatorman::~Translatorman()
{
    /// Destructor

    delete ui;
    delete mui_toolbar;
    delete mui_file;
    delete mui_edit;
    delete mui_view;
    delete mui_help;
    delete mui_tabs;
    delete m_showedToolbar;
    delete m_ngroff;
    delete m_graphic;
    delete m_statusbar;
}

void Translatorman::on_actionAbout_Pamcli_triggered()
{
    tlWebBrowser("http://manualencatala.tk/");
}

void Translatorman::on_actionAbout_Translatorman_triggered()
{
    AboutTranslatorman *aboutit = new AboutTranslatorman();
    aboutit->show();
}

void Translatorman::on_actionShow_toolbar_triggered(bool checked)
{
    if (checked == true)
    {
        mui_toolbar->show();
    } else
    {
        mui_toolbar->hide();
    } // end if
}

void Translatorman::on_actionShow_in_ngroff_triggered(bool checked)
{
    if (checked == true)
    {
        //mui_toolbar->show();
        m_statusbar->showMessage("View in nroff");
        m_graphic->setChecked(false);
    } else
    {
        //mui_toolbar->hide();
        m_statusbar->showMessage("View in graphic");
        m_graphic->setChecked(true);
    } // end if
}

void Translatorman::on_actionShow_graphic_triggered(bool checked)
{
    if (checked == true)
    {
        //mui_toolbar->show();
        m_statusbar->showMessage("View in graphic");
        m_ngroff->setChecked(false);

    } else
    {
        //mui_toolbar->hide();
        m_statusbar->showMessage("View in nroff");
        m_ngroff->setChecked(true);
    } // end if
}



void Translatorman::on_actionFull_screen_triggered()
{
    pantallacompleta();
}

void Translatorman::pantallacompleta()
{
    if ( isFullScreen() ) {
        showNormal();
    } else {
        showFullScreen();
    } // end if
}

int Translatorman::on_actionPreferences_triggered()
{
    try {
        TsPreference *diag = new TsPreference();
        diag->show();
        return 0;
    } catch (...) {
        return 1;
    } // end try

    return 0;

}
void Translatorman::addingTab() {
    mui_tabs->addTab(new QTextEdit(),"TAB " + QString::number(tab_counter) );
    tab_list << "TAB " + QString::number(tab_counter);
    tab_counter+=1;
}

void Translatorman::closeTab()
{
    /// Remove the tab
    if(!tab_list.isEmpty()){
        int tabindex = tab_list.indexOf(mui_tabs->tabText(mui_tabs->currentIndex()));
        mui_tabs->widget(mui_tabs->currentIndex())->deleteLater();
        mui_tabs->removeTab(mui_tabs->currentIndex());
        tab_list.removeAt(tabindex);
    }
    // end if
}
void Translatorman::closeSelectTab(int index)
{
    /// Remove the tab
    //widget(index)->~QWidget();
    //QWidget(index).close();
    if(!tab_list.isEmpty()){
        int tabindex = tab_list.indexOf(mui_tabs->tabText(index));
        mui_tabs->widget(index)->deleteLater();
        mui_tabs->removeTab(index);
        tab_list.removeAt(tabindex);
    }
    // end if
}

void Translatorman::closeAll()
{
    /// Remove all tabs
    if(!tab_list.isEmpty()){
        foreach (QString str, tab_list) {
            mui_tabs->widget(tab_list.indexOf(str))->deleteLater();
            tab_list.removeAt(tab_list.indexOf(str));
        } // end for
        mui_tabs->clear();
    } // end if
}

void Translatorman::on_actionCut_triggered() {
    QTextEdit* p_text = dynamic_cast<QTextEdit*>(mui_tabs->currentWidget());
    if (p_text)
    {
        // it was a text, perform cut
        p_text->cut();
    }
}

void Translatorman::on_actionCopy_triggered()
{
    //mui_tabs->currentWidget()
    QTextEdit* p_text = dynamic_cast<QTextEdit*>(mui_tabs->currentWidget());
    if (p_text)
    {
        // it was a text, perform copy
        p_text->copy();
    } // end if
}

void Translatorman::on_actionPaste_triggered()
{
    QTextEdit* p_text = dynamic_cast<QTextEdit*>(mui_tabs->currentWidget());
    if (p_text)
    {
        // it is a text, perform paste
        p_text->paste();
    } // end if
}

void Translatorman::on_actionDelete_triggered()
{
    QTextEdit* p_text = dynamic_cast<QTextEdit*>(mui_tabs->currentWidget());
    if (p_text)
    {
         // it was a text, perform delete
        p_text->textCursor().removeSelectedText();
    } // end if
}

void Translatorman::on_actionUndo_triggered()
{
    QTextEdit* p_text = dynamic_cast<QTextEdit*>(mui_tabs->currentWidget());
    if (p_text)
    {
        p_text->undo();
    } // end if
}

void Translatorman::on_actionRedo_triggered()
{
    QTextEdit* p_text = dynamic_cast<QTextEdit*>(mui_tabs->currentWidget());
    if (p_text)
    {
        p_text->redo();
    } // end if
}

void Translatorman::closeAllExcept()
{
    /// Remove all tabs except current
    QString currentname = mui_tabs->tabText(mui_tabs->currentIndex());
    int mui_index_in_tab_list = tab_list.indexOf(currentname);
    if ( !tab_list.isEmpty() ) {
        for (QStringList::iterator it = tab_list.begin(); it != tab_list.end(); ++it) {
            QString iter = *it;
            if ( iter != currentname ) {
                mui_tabs->widget(QString::number(tab_list.indexOf(iter.toAscii())).toInt())->deleteLater();
            } // end if
        } // end for
        tab_list.clear();
        tab_list << currentname;
    } // end if
}

void Translatorman::openFile(const QString &filechosed)
{
    /// Open desired file
    QFile textfile( filechosed );
    if (textfile.open(QIODevice::ReadOnly))
    {
        // Declare pointers and variables
        QTextStream text_stream(&textfile);
        QFileInfo file_info(textfile);


        QTextEdit *text_edit = new QTextEdit();
        //DocumentWindow *text_edit = new DocumentWindow();
        // Call methods
        //QString manpage = tlman2html(text_stream.readAll());
        QString manpage = tlman2html(filechosed);

        text_edit->setHtml(manpage);
        mui_tabs->addTab(text_edit, file_info.fileName() );
        tab_list << file_info.fileName();
    } // end if
    textfile.close();
}

void Translatorman::on_actionOpen_triggered()
{
    /// Open file dialog
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Manpages (*.1 *.2 *.3 *.4 *.5 *.6 *.7 *.8 *.9)");
    openFile(fileName);
}

