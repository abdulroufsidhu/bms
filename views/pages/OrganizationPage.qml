import QtQuick 2.0
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.0
import "../"
import "../components"
import "../basicComponents/buttons"

Page {
	onFocusChanged: {
		if (focus) title_bar.window_title = "Organization"
	}
	background: Rectangle { anchors.fill: parent; color: rootWindow.secondary_color }
	padding: rootWindow.pixel_font_size*10
	MyListView{
		id: lv_orgs
		lv_model: 6
		sell_btn_item: true
		anchors {
			top: parent.top;
			left: parent.left;
			bottom: org_branch_separator.top
		}
		width: rootWindow.width * 0.7
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

	MyListView{
		id: lv_branches
		lv_model: 60
		sell_btn_item: true
		anchors {
			top: org_branch_separator.top;
			left: parent.left;
			bottom: parent.bottom;
			topMargin: pixel_font_size*20
			bottomMargin: pixel_font_size*20
		}
		width: rootWindow.width * 0.7
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
