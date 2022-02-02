import QtQuick 2.15
import QtQuick.Controls 2.15
import "./organizations/"
import "../basicComponents/buttons"

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
			spacing: rootWindow.pixel_font_size * 10
			Text {
				id: lv_txt_delegate
				width: lv.width - ( sell_item_btn.implicitContentWidth + btn_select.implicitContentWidth + view_item_btn.implicitContentWidth + manage_org_btn.implicitContentWidth + (parent.spacing * total_btns) )
				text: parent.fetchTextPattern()
				font: rootWindow.font
				elide: Text.ElideLeft
				verticalAlignment: Text.AlignVCenter
				horizontalAlignment: Text.AlignLeft
				color: rootWindow.primary_text_color
			}

			MyButton {
				id: manage_org_btn;
				btn_font_pixel_size: pixel_font_size_24
				add_width: 16
				add_height: 16
				btn_text_color: secondary_text_color;
				btn_text: "🛠️";
				btn_col: primary_button_color;
				anchors.verticalCenter: lvd_row.verticalCenter
				visible: manage_btn_org;
			}

			MyButton {
				id: view_item_btn;
				btn_font_pixel_size: pixel_font_size_24
				add_width: 16
				add_height: 16
				btn_text_color: secondary_text_color;
				btn_text: "👁️";
				btn_col: primary_button_color;
				anchors.verticalCenter: lvd_row.verticalCenter
				onClicked: parent.viewButtonClicked()
				visible: view_btn_item;
			}

			MyButton {
				id: sell_item_btn;
				btn_font_pixel_size: pixel_font_size_24
				add_width: 16
				add_height: 16
				btn_text_color: secondary_text_color;
				btn_text: "SELL";
				btn_col: primary_button_color;
				anchors.verticalCenter: lvd_row.verticalCenter
				visible: sell_btn_item;
			}

			MyButton {
				id: btn_select;
				btn_font_pixel_size: pixel_font_size_24
				add_width: 16
				add_height: 16
				btn_text_color: secondary_text_color;
				btn_text: "SELECT";
				btn_col: primary_button_color;
				anchors.verticalCenter: lvd_row.verticalCenter
				onClicked: parent.selectButtonClicked()
				visible: select_btn;
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
					view_org_popup.name = model.name
					view_org_popup.email = model.email
					view_org_popup.contact = model.contact
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
