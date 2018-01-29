/**************************************************************************
* Otter Browser: Web browser controlled by the user, not vice-versa.
* Copyright (C) 2013 - 2018 Michal Dutkiewicz aka Emdek <michal@emdek.pl>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
**************************************************************************/

#ifndef OTTER_TRANSFERSCONTENTSWIDGET_H
#define OTTER_TRANSFERSCONTENTSWIDGET_H

#include "../../../core/TransfersManager.h"
#include "../../../ui/ContentsWidget.h"
#include "../../../ui/ItemDelegate.h"

#include <QtGui/QStandardItemModel>

namespace Otter
{

namespace Ui
{
	class TransfersContentsWidget;
}

class Window;

class ProgressBarDelegate final : public ItemDelegate
{
public:
	explicit ProgressBarDelegate(QObject *parent);

	void setEditorData(QWidget *editor, const QModelIndex &index) const override;
	QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

class TransfersContentsWidget final : public ContentsWidget
{
	Q_OBJECT

public:
	enum DataRole
	{
		BytesReceivedRole = Qt::UserRole,
		BytesTotalRole,
		InstanceRole,
		ProgressRole,
		StateRole,
		TimeFinishedRole,
		TimeStartedRole
	};

	explicit TransfersContentsWidget(const QVariantMap &parameters, Window *window, QWidget *parent);
	~TransfersContentsWidget();

	void print(QPrinter *printer) override;
	QString getTitle() const override;
	QLatin1String getType() const override;
	QUrl getUrl() const override;
	QIcon getIcon() const override;
	ActionsManager::ActionDefinition::State getActionState(int identifier, const QVariantMap &parameters = {}) const override;
	WebWidget::LoadingState getLoadingState() const override;
	bool eventFilter(QObject *object, QEvent *event) override;

public slots:
	void triggerAction(int identifier, const QVariantMap &parameters = {}) override;

protected:
	void changeEvent(QEvent *event) override;
	Transfer* getTransfer(const QModelIndex &index) const;
	int findTransfer(Transfer *transfer) const;

protected slots:
	void removeTransfer();
	void openTransfer();
	void openTransferFolder();
	void copyTransferInformation();
	void stopResumeTransfer();
	void redownloadTransfer();
	void startQuickTransfer();
	void clearFinishedTransfers();
	void handleTransferAdded(Transfer *transfer);
	void handleTransferChanged(Transfer *transfer);
	void handleTransferRemoved(Transfer *transfer);
	void showContextMenu(const QPoint &position);
	void updateActions();

private:
	QStandardItemModel *m_model;
	bool m_isLoading;
	Ui::TransfersContentsWidget *m_ui;
};

}

#endif
