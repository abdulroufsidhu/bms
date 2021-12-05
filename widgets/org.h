#ifndef ORG_H
#define ORG_H

#include <QWidget>
#include <QMessageBox>
#include <QListWidgetItem>
#include "./libs/api.h"
#include <./libs/email.h>
#include <./libs/user.h>
#include "./OrganizationTab/hire.h"

namespace Ui {
	class Organization;
}

class Org : public QWidget
{
	Q_OBJECT

public:
	explicit Org(QWidget *parent = nullptr);
	~Org ();

	void updateLWOrg();

	void orgInfoPage();

	void updateLWBranches();

private slots:
	void on_btn_register_clicked();

	void on_btn_relocate_clicked();

	void on_btn_revoke_clicked();

	void on_btn_add_branch_clicked();

	void on_btn_hire_clicked();

	void on_tabWidget_2_currentChanged(int index);

	void on_lw_organizations_doubleClicked(const QModelIndex &index);

	void on_tabWidget_currentChanged(int index);

	void on_tabWidget_org_and_branch_currentChanged(int index);

	void on_lw_branches_doubleClicked(const QModelIndex &index);

private:
	Ui::Organization *ui;
};

#endif // ORG_H
