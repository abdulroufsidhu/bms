import QtQuick 2.0
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.0
import "../"
import "../components"
import "../components/organizations/"
import "../basicComponents/buttons"

Page {
	onFocusChanged: {
		if (focus) title_bar.window_title = "Organization"
	}
	background: Rectangle { anchors.fill: parent; color: rootWindow.secondary_color }
	padding: rootWindow.pixel_font_size*10

	Rectangle {
		id: lv_orgs
		anchors {
			top: parent.top;
			left: parent.left;
			bottom: org_branch_separator.top
		}
		anchors.bottomMargin: pixel_font_size_24
		width: rootWindow.width * 0.7
		color: primary_color
		radius: rootWindow.pixel_font_size * 10

		MyListView{
			model: _organization_list
			manage_btn_org: true
			select_btn: true
			view_btn_item: true
			anchors.fill: parent
			orgList: true
		}

	}

	DropShadow {
		anchors.fill: lv_orgs
		source: lv_orgs
		radius: 16
		samples: 33
	}

	MyButton {
		btn_text: "<b>➕ Organization</b>"
		btn_font_pixel_size: rootWindow.pixel_font_size_24
		anchors {
			top: lv_orgs.TopRight
			left: lv_orgs.right
			leftMargin: rootWindow.pixel_font_size*20
			right: parent.right
		}

		MouseArea {
			anchors.fill: parent
			onClicked: {
				stack.push(add_org_comp)
			}
		}

	}

	Component {
		id: add_org_comp
		AddOrganization {}
	}

	Rectangle {
		id: org_branch_separator
		color: rootWindow.primary_color
		width: rootWindow.width
		height: rootWindow.pixel_font_size*1
		y: rootWindow.height/3
		x: -rootWindow.pixel_font_size*10
	}

	DropShadow {
		anchors.fill: org_branch_separator
		source: org_branch_separator
		radius: 16
		samples: 33
		color: rootWindow.primary_color
	}

	Rectangle {
		id: lv_branches
		anchors {
			top: org_branch_separator.bottom;
			left: parent.left;
			bottom: parent.bottom;
			topMargin: pixel_font_size_24
			bottomMargin: pixel_font_size_24
		}
		width: rootWindow.width * 0.7
		color: primary_color
		radius: rootWindow.pixel_font_size * 10

		MyListView{
			anchors.fill: parent
			model: _branch_list
			sell_btn_item: true
			branchList: true
		}
	}

	DropShadow {
		anchors.fill: lv_branches
		source: lv_branches
		radius: 16
		samples: 33
	}

	MyButton {
		btn_text: "<b>➕ Branches</b>"
		btn_font_pixel_size: rootWindow.pixel_font_size_24
		anchors {
			top: org_branch_separator.bottom
			left: lv_branches.right
			leftMargin: rootWindow.pixel_font_size*20
			topMargin: rootWindow.pixel_font_size*20
			right: parent.right
		}
	}

}
