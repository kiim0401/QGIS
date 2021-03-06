/***************************************************************************
                             qgsreportorganizerwidget.cpp
                             ------------------------
    begin                : December 2017
    copyright            : (C) 2017 by Nyall Dawson
    email                : nyall dot dawson at gmail dot com
 ***************************************************************************/
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "qgsreportorganizerwidget.h"
#include "qgsreport.h"
#include "qgsreportsectionmodel.h"
#include "qgsreportsectionlayout.h"
#include "qgsreportsectionfieldgroup.h"
#include "qgslayout.h"
#include "qgslayoutdesignerdialog.h"
#include "qgsreportlayoutsectionwidget.h"
#include "qgsreportsectionwidget.h"
#include "qgsreportfieldgroupsectionwidget.h"
#include <QMenu>
#include <QMessageBox>

#ifdef ENABLE_MODELTEST
#include "modeltest.h"
#endif

QgsReportOrganizerWidget::QgsReportOrganizerWidget( QWidget *parent, QgsLayoutDesignerDialog *designer, QgsReport *report )
  : QgsPanelWidget( parent )
  , mReport( report )
  , mDesigner( designer )
{
  setupUi( this );
  setPanelTitle( tr( "Report" ) );

  mSectionModel = new QgsReportSectionModel( mReport, this );
  mViewSections->setModel( mSectionModel );
  mViewSections->expandAll();

#ifdef ENABLE_MODELTEST
  new ModelTest( mSectionModel, this );
#endif

  QVBoxLayout *vLayout = new QVBoxLayout();
  vLayout->setMargin( 0 );
  vLayout->setSpacing( 0 );
  mSettingsFrame->setLayout( vLayout );

  mViewSections->setEditTriggers( QAbstractItemView::AllEditTriggers );

  QMenu *addMenu = new QMenu( mButtonAddSection );
  QAction *layoutSection = new QAction( tr( "Single section" ), addMenu );
  addMenu->addAction( layoutSection );
  connect( layoutSection, &QAction::triggered, this, &QgsReportOrganizerWidget::addLayoutSection );
  QAction *fieldGroupSection = new QAction( tr( "Field group" ), addMenu );
  addMenu->addAction( fieldGroupSection );
  connect( fieldGroupSection, &QAction::triggered, this, &QgsReportOrganizerWidget::addFieldGroupSection );

  connect( mViewSections->selectionModel(), &QItemSelectionModel::currentChanged, this, &QgsReportOrganizerWidget::selectionChanged );

  mButtonAddSection->setMenu( addMenu );
  connect( mButtonRemoveSection, &QPushButton::clicked, this, &QgsReportOrganizerWidget::removeSection );
  mButtonRemoveSection->setEnabled( false ); //disable until section clicked
}

void QgsReportOrganizerWidget::setMessageBar( QgsMessageBar *bar )
{
  mMessageBar = bar;
}

void QgsReportOrganizerWidget::setEditedSection( QgsAbstractReportSection *section )
{
  mSectionModel->setEditedSection( section );
}

void QgsReportOrganizerWidget::addLayoutSection()
{
  std::unique_ptr< QgsReportSectionLayout > section = qgis::make_unique< QgsReportSectionLayout >();
  QgsAbstractReportSection *newSection = section.get();
  mSectionModel->addSection( mViewSections->currentIndex(), std::move( section ) );
  QModelIndex newIndex = mSectionModel->indexForSection( newSection );
  mViewSections->setCurrentIndex( newIndex );
}

void QgsReportOrganizerWidget::addFieldGroupSection()
{
  std::unique_ptr< QgsReportSectionFieldGroup > section = qgis::make_unique< QgsReportSectionFieldGroup >();
  QgsAbstractReportSection *newSection = section.get();
  mSectionModel->addSection( mViewSections->currentIndex(), std::move( section ) );
  QModelIndex newIndex = mSectionModel->indexForSection( newSection );
  mViewSections->setCurrentIndex( newIndex );
}

void QgsReportOrganizerWidget::removeSection()
{
  QgsAbstractReportSection *section = mSectionModel->sectionForIndex( mViewSections->currentIndex() );
  if ( dynamic_cast< QgsReport * >( section ) )
    return; //report cannot be removed

  int res = QMessageBox::question( this, tr( "Remove Section" ),
                                   tr( "Are you sure you want to remove the report section?" ),
                                   QMessageBox::Yes | QMessageBox::No, QMessageBox::No );
  if ( res == QMessageBox::No )
    return;

  mSectionModel->removeRow( mViewSections->currentIndex().row(), mViewSections->currentIndex().parent() );
}

void QgsReportOrganizerWidget::selectionChanged( const QModelIndex &current, const QModelIndex & )
{
  QgsAbstractReportSection *parent = mSectionModel->sectionForIndex( current );
  if ( !parent )
    parent = mReport;

  // report cannot be deleted
  mButtonRemoveSection->setEnabled( parent != mReport );

  delete mConfigWidget;
  if ( QgsReportSectionLayout *section = dynamic_cast< QgsReportSectionLayout * >( parent ) )
  {
    QgsReportLayoutSectionWidget *widget = new QgsReportLayoutSectionWidget( this, mDesigner, section );
    mSettingsFrame->layout()->addWidget( widget );
    mConfigWidget = widget;
  }
  else if ( QgsReportSectionFieldGroup *section = dynamic_cast< QgsReportSectionFieldGroup * >( parent ) )
  {
    QgsReportSectionFieldGroupWidget *widget = new QgsReportSectionFieldGroupWidget( this, mDesigner, section );
    mSettingsFrame->layout()->addWidget( widget );
    mConfigWidget = widget;
  }
  else if ( QgsReport *section = dynamic_cast< QgsReport * >( parent ) )
  {
    QgsReportSectionWidget *widget = new QgsReportSectionWidget( this, mDesigner, section );
    mSettingsFrame->layout()->addWidget( widget );
    mConfigWidget = widget;
  }
  else
  {
    mConfigWidget = nullptr;
  }
}
