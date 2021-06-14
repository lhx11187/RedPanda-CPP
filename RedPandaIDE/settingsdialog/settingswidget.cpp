#include "settingswidget.h"

#include <QAbstractItemView>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QListView>
#include <QPlainTextEdit>
#include <QSpinBox>
#include "../widgets/coloredit.h"

SettingsWidget::SettingsWidget(const QString &name, const QString &group, QWidget *parent):
    QWidget(parent),
    mName(name),
    mGroup(group)
{

}

void SettingsWidget::init()
{
    load();
    connectInputs();
}

void SettingsWidget::load()
{
    doLoad();
    clearSettingsChanged();
}

void SettingsWidget::save()
{
    doSave();
    clearSettingsChanged();
}

void SettingsWidget::connectAbstractItemView(QAbstractItemView *pView)
{
    connect(pView->model(),&QAbstractItemModel::rowsInserted,this,&SettingsWidget::setSettingsChanged);
    connect(pView->model(),&QAbstractItemModel::rowsMoved,this,&SettingsWidget::setSettingsChanged);
    connect(pView->model(),&QAbstractItemModel::rowsRemoved,this,&SettingsWidget::setSettingsChanged);
    connect(pView->model(),&QAbstractItemModel::dataChanged,this,&SettingsWidget::setSettingsChanged);
    connect(pView->model(),&QAbstractItemModel::modelReset,this,&SettingsWidget::setSettingsChanged);
}

void SettingsWidget::disconnectAbstractItemView(QAbstractItemView *pView)
{
    disconnect(pView->model(),&QAbstractItemModel::rowsInserted,this,&SettingsWidget::setSettingsChanged);
    disconnect(pView->model(),&QAbstractItemModel::rowsMoved,this,&SettingsWidget::setSettingsChanged);
    disconnect(pView->model(),&QAbstractItemModel::rowsRemoved,this,&SettingsWidget::setSettingsChanged);
    disconnect(pView->model(),&QAbstractItemModel::dataChanged,this,&SettingsWidget::setSettingsChanged);
    disconnect(pView->model(),&QAbstractItemModel::modelReset,this,&SettingsWidget::setSettingsChanged);

}

void SettingsWidget::connectInputs()
{
    for (QLineEdit* p:findChildren<QLineEdit*>()) {
        connect(p, &QLineEdit::textChanged, this, &SettingsWidget::setSettingsChanged);
    }
    for (QCheckBox* p:findChildren<QCheckBox*>()) {
        connect(p, &QCheckBox::stateChanged, this, &SettingsWidget::setSettingsChanged);
    }
    for (QPlainTextEdit* p:findChildren<QPlainTextEdit*>()) {
        connect(p, &QPlainTextEdit::textChanged, this, &SettingsWidget::setSettingsChanged);
    }
    for (QSpinBox* p:findChildren<QSpinBox*>()) {
        connect(p, QOverload<int>::of(&QSpinBox::valueChanged), this, &SettingsWidget::setSettingsChanged);
    }
    for (ColorEdit* p:findChildren<ColorEdit*>()) {
        connect(p, &ColorEdit::colorChanged, this, &SettingsWidget::setSettingsChanged);
    }
    for (QComboBox* p: findChildren<QComboBox*>()) {
        connect(p, QOverload<int>::of(&QComboBox::currentIndexChanged) ,this, &SettingsWidget::setSettingsChanged);
    }
    for (QAbstractItemView* p: findChildren<QAbstractItemView*>()) {
        connectAbstractItemView(p);
    }

}

void SettingsWidget::disconnectInputs()
{
    for (QLineEdit* p:findChildren<QLineEdit*>()) {
        disconnect(p, &QLineEdit::textChanged, this, &SettingsWidget::setSettingsChanged);
    }
    for (QCheckBox* p:findChildren<QCheckBox*>()) {
        disconnect(p, &QCheckBox::stateChanged, this, &SettingsWidget::setSettingsChanged);
    }
    for (QPlainTextEdit* p:findChildren<QPlainTextEdit*>()) {
        disconnect(p, &QPlainTextEdit::textChanged, this, &SettingsWidget::setSettingsChanged);
    }
    for (QComboBox* p: findChildren<QComboBox*>()) {
        disconnect(p, QOverload<int>::of(&QComboBox::currentIndexChanged) ,this, &SettingsWidget::setSettingsChanged);
    }
    for (QAbstractItemView* p: findChildren<QAbstractItemView*>()) {
        disconnectAbstractItemView(p);
    }
}

const QString &SettingsWidget::group()
{
    return mGroup;
}

const QString &SettingsWidget::name()
{
    return mName;
}

bool SettingsWidget::isSettingsChanged()
{
    return mSettingsChanged;
}

void SettingsWidget::setSettingsChanged()
{
    mSettingsChanged = true;
    emit settingsChanged(true);
}

void SettingsWidget::clearSettingsChanged()
{
    mSettingsChanged = false;
    emit settingsChanged(false);
}