import QtQuick 2.15
import QtQuick.Controls 2.15
import "./organizations/"

ListView {
	property bool view_btn_item: false
	property bool sell_btn_item: false
	property bool manage_btn_org: false
	property bool select_btn: false

	property int total_btns: 0

	property bool orgList: false
	property bool branchList: false
	property bool itemsList: false

	onView_btn_itemChanged: {
		if (view_btn_item == true) ++total_btns;
		if (view_btn_item == false) --total_btns;
	}
	onSell_btn_itemChanged: {
		if (sell_btn_item == true) ++total_btns;
		if (sell_btn_item == false) --total_btns;
	}
	onManage_btn_orgChanged: {
		if (manage_btn_org == true) ++total_btns;
		if (manage_btn_org == false) --total_btns;
	}
	onSelect_btnChanged: {
		if (select_btn == true ) ++total_btns;
		if (select_btn == false) --total_btns;
	}

	id: lv
	anchors.topMargin: rootWindow.pixel_font_size_24
	anchors.bottomMargin: rootWindow.pixel_font_size_24
	cacheBuffer: rootWindow.pixel_font_size * 40
	spacing: rootWindow.pixel_font_size*6
	clip: true

	ScrollBar.vertical: ScrollBar{  }


	delegate: ItemDelegate{
		width: lv.width
		implicitHeight: lvd_row.implicitHeight;
		Row {
			anchors.centerIn: parent
			id: lvd_row
			//				implicitHeight: lv_txt_delegate.implicitHeight
			spacing: rootWindow.pixel_font_size * 10
			Text {
				id: lv_txt_delegate
				width: lv.width -( view_item_btn.width + sell_item_btn.width + manage_org_btn.width + btn_select.width + parent.spacing*(total_btns) + rootWindow.pixel_font_size_24 )
				text: parent.fetchTextPattern()
				font: rootWindow.font
				elide: Text.ElideLeft
				verticalAlignment: Text.AlignVCenter
				horizontalAlignment: Text.AlignLeft
				color: rootWindow.primary_text_color
			}
			Image {
				id: manage_org_btn;
				opacity: 0.7
				source: "qrc:/icons/icons/process.svg";
				visible: manage_btn_org;
				width: visible ? rootWindow.pixel_font_size * sourceSize.width/3.56 : 0
				height: rootWindow.pixel_font_size * sourceSize.height/3.56
				anchors.verticalCenter: lvd_row.verticalCenter
				MouseArea {
					anchors.fill: parent
					hoverEnabled: true;
					onEntered: parent.opacity = 1;
					onExited: parent.opacity = 0.7;
				}
			}

			Image {
				id: view_item_btn;
				opacity: 0.7
				source: "qrc:/icons/icons/view 1.svg";
				visible: view_btn_item;
				width: visible ? rootWindow.pixel_font_size * sourceSize.width/2 : 0
				height: rootWindow.pixel_font_size * sourceSize.height/2
				anchors.verticalCenter: lvd_row.verticalCenter
				MouseArea {
					anchors.fill: parent
					onClicked: parent.parent.viewButtonClicked();
					hoverEnabled: true;
					onEntered: parent.opacity = 1;
					onExited: parent.opacity = 0.7;
				}
			}
			Image {
				id: sell_item_btn;
				opacity: 0.7
				source: "qrc:/icons/icons/sell-label 1.svg";
				visible: sell_btn_item;
				width: visible ? rootWindow.pixel_font_size * sourceSize.width/2 : 0
				height: rootWindow.pixel_font_size * sourceSize.height/2
				anchors.verticalCenter: lvd_row.verticalCenter

				MouseArea {
					anchors.fill: parent
					hoverEnabled: true;
					onEntered: parent.opacity = 1;
					onExited: parent.opacity = 0.7;
				}
			}
			Image {
				id: btn_select
				opacity: 0.7
				source: "qrc:/icons/icons/SelectButton.svg"
				visible: select_btn;
				width: visible ? rootWindow.pixel_font_size * sourceSize.width/2:0;
				height: visible ? rootWindow.pixel_font_size * sourceSize.height/2:0;
				anchors.verticalCenter: lvd_row.verticalCenter
				MouseArea {
					anchors.fill: parent
					onClicked: parent.parent.selectButtonClicked();
					hoverEnabled: true;
					onEntered: parent.opacity = 1;
					onExited: parent.opacity = 0.7;
				}
			}

			function selectButtonClicked() {
				if (orgList) {
					txt_notification_text = _branch_list.refresh(model.id);
					if (!txt_notification_text.length) {
						txt_notification_text = "Please Also Select Branch"
						txt_popup_col = red_color
					}
					return
				}
				if (branchList) {
					_current_user.getEmpByBranchId(model.id , _current_user.id);
					return
				}
			}
			function fetchTextPattern() {
				if (orgList) return "Name: " + model.name + "®️\n📧: " + model.email + "\n📞: " + model.contact + "\nBusiness Number: " + model.gov_reg_num;
				else if (branchList) return "Name: " + model.name + "®️\n📧: " + model.email + "\n📞: " + model.contact + "\nBranch Code: " + model.code;
				else if (itemsList) return "Item Name: " + model.name + "\n📧: " + model.email + "\n📞: " + model.contact
			}
			function viewButtonClicked() {
				if (orgList) {
					view_org_popup.open();
				}
			}

			Component {
				id: v_o_component;
				ViewOrganization {
					id: view_organization
					name: model.name
					email: model.email
					contact: model.contact
				}
			}

		}

		hoverEnabled: true

		background: Rectangle {
			anchors.fill: lvd_row;
			color: parent.hovered?secondary_color:primary_color
			opacity: 0.5
			radius: pixel_font_size*5
		}
	}

	Connections {
		target: _current_user
		function onRecievedEmpByBranchId(r) {
			txt_notification_text = r
			if (!txt_notification_text.length) {
				txt_notification_text = "SUCCESS You Are SETUP";
				txt_popup_col = rootWindow.green_color;
			}
		}
	}

}
