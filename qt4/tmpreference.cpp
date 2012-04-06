/*
 * tmpreference.cpp
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

#include "tmpreference.h"
#include "stdlib.h"
#include "stdio.h"

//TsPreference::TsPreference(QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui_TsPreference)
TsPreference::TsPreference(QWidget *parent) :
    QDialog(parent), ui(new Ui::TsPreference)
{
    ui->setupUi(this);
    mui_pathroute = ui->mui_pathroute;
    mui_tabwith = ui->mui_tabwith;
    mui_messagestatus = ui->mui_messagestatus;
    mui_minutes = ui->mui_minutes;
    mui_combotoolbar = ui->mui_combotoolbar;

    mui_tabwith->setValue(4);
    m_statusbar = true;
    m_tabvalue = mui_tabwith->value();

    //setupUi(this);
    #ifndef Q_OS_WIN32
        CAD_HOME = tlGetEnv ( "HOME" );
    #else
        CAD_HOME = tlGetEnv ( "UserProfile" );
    #endif // Q_OS_WIN32
}

TsPreference::~TsPreference()
{
    //delete ui;
}

void TsPreference::on_mui_cancel_clicked()
{
    this->close();
}

void TsPreference::on_mui_accept_clicked()
{
    QString program = "fuckyou";
    applychanges();
    fprintf(stderr,program.toAscii());
    this->close();
}

void TsPreference::on_mui_apply_clicked()
{
    applychanges();
}

/*void TsPreference::on_mui_cleanpath_clicked()
{
    mui_pathroute->setText("");
}*/

void TsPreference::on_mui_filepath_clicked()
{
    m_foldername = QFileDialog::getExistingDirectory ( this, tr("Open Directory"), CAD_HOME, QFileDialog::ShowDirsOnly );
    mui_pathroute->setText ( m_foldername );
}

void TsPreference::on_mui_detectwidth_clicked(bool checked)
{
    if (checked == true)
    {
        mui_tabwith->setDisabled( true );
        m_tabvalue = 2;
    } else
    {
        mui_tabwith->setEnabled( true );
        m_tabvalue = mui_tabwith->value();
    } // end if

}

void TsPreference::on_mui_showstatusbar_clicked(bool checked)
{

    if (checked == true)
    {
        mui_messagestatus->setEnabled(true);
        m_statusbar = true;
    } else {
        mui_messagestatus->setDisabled(true);
        m_statusbar = false;
    } // end if
}

void TsPreference::on_mui_messagestatus_clicked(bool checked)
{
    if (checked == true)
    {
        m_statusbar = true;
    } else {
        m_statusbar = false;
    } // end if
}

void TsPreference::on_mui_autosave_clicked(bool checked)
{
    if (checked == true)
    {
        mui_minutes->setEnabled(true);
    } else
    {
        mui_minutes->setDisabled(true);
        mui_minutes->setValue(0);
    } // end if
}

void TsPreference::on_mui_showtoolbar_clicked(bool checked)
{
    if (checked == true)
    {
        mui_combotoolbar->setEnabled(true);
    }
    else {
        mui_combotoolbar->setDisabled(true);
    } // end if

}


int TsPreference::applychanges()
{
    QString program = "apply";
    try {
        fprintf(stderr,program.toAscii());
        return 0;
    } catch (...) {
        fprintf(stderr, tr("Something was wrong").toAscii());
        return 1;
    } // end try
}
