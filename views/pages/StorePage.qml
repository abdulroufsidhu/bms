import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "../"
import "../basicComponents/inputs"
import "../basicComponents/buttons"
import "../components"
import QtGraphicalEffects 1.0

Page {
	onFocusChanged: {
		if (focus) title_bar.window_title = "Store"
	}
	background: Rectangle { anchors.fill: parent; color: rootWindow.transparent_color }

	padding: pixel_font_size *10

	RowLayout {
		id: row_search_params
		anchors{
			top: parent.top
			left: parent.left
			right: parent.right
		}

		spacing: pixel_font_size*10
		MyComboBox {
			model_data_array: _row_to_search
			Layout.fillWidth: true
			Layout.minimumHeight:  et_search.height
		}

		MyComboBox {
			model_data_array: [
				qsTr("Inventory"),
				qsTr("Sold")
			]
			Layout.fillWidth: true
			Layout.minimumHeight: et_search.height
		}

		MyEditText {
			id: et_search
			Layout.minimumWidth: rootWindow.wr * 150
		}

		MyCircularButton {
			id: btn_search
			btn_text: "🔍"
			btn_text_color: rootWindow.primary_button_color
			btn_text_font_size: rootWindow.pixel_font_size_24*1.5
			color: rootWindow.primary_color
			border {
				color: primary_button_color
				width: rootWindow.pixel_font_size*2
			}
		}


	}

	MyCircularButton {
		id: btn_add_item
		btn_text: "➕"
		btn_text_color: rootWindow.secondary_text_color
		btn_text_font_size: rootWindow.pixel_font_size_24*2
		rect_color: rootWindow.primary_button_color
		anchors{
			horizontalCenter: row_search_params.horizontalCenter
			top: row_search_params.bottom
			margins: rootWindow.pixel_font_size*5
		}
	}

	Rectangle {
		id: mlv_store
		anchors.top: btn_add_item.bottom
		anchors.bottom: parent.bottom
		anchors.margins: rootWindow.pixel_font_size*20
		anchors.horizontalCenter: row_search_params.horizontalCenter
		width: rootWindow.width - rootWindow.pixel_font_size*100
		color: primary_color
		radius: rootWindow.pixel_font_size * 10
		MyListView {
			model: _organization_list
			sell_btn_item: true
			view_btn_item: true
			anchors.fill: parent
			itemsList: true
		}

	}


	DropShadow {
		anchors.fill: mlv_store
		radius: 32
		samples: 65
		source: mlv_store
	}

}

/*##^##
Designer {
		D{i:0;autoSize:true;formeditorZoom:1.5;height:480;width:640}
}
##^##*/
