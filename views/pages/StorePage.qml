import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "../"
import "../basicComponents/inputs"
import "../basicComponents/buttons"
import "../components"

Page {
	onFocusChanged: {
		if (focus) title_bar.window_title = "Store"
	}
	background: Rectangle { anchors.fill: parent; color: rootWindow.transparent_color }

	Row {
		id: row_search_params
		anchors{
			top: parent.top
			horizontalCenter: parent.horizontalCenter
			margins: 20
		}

		spacing: 10
		MyComboBox {
			model_data_array: [
				qsTr("Item ID")
				, qsTr("Item Menufecturer")
				, qsTr("Item Vendor")
				, qsTr("Item Serial")
				, qsTr("Item Price")
				, qsTr("Item Name")
				, qsTr("Customer Name")
				, qsTr("Customer Contact")
				, qsTr("Customer National ID")
			]
			cb_width: rootWindow.wr * 280
			height: et_search.height
		}

		MyComboBox {
			model_data_array: [ qsTr("Inventory"), qsTr("Sold") ]
			height: et_search.height
		}

		MyEditText {
			id: et_search
			width: rootWindow.wr * 150
		}

		MyCircularButton {
			btn_text: "🔍"
			btn_text_color: rootWindow.primary_button_color
			btn_text_font_size: rootWindow.pixel_font_size_24
			color: rootWindow.primary_color
		}

	}

	MyCircularButton {
		id: btn_add_item
		btn_text: "+"
		btn_text_color: rootWindow.secondary_text_color
		btn_text_font_size: rootWindow.pixel_font_size_24
		rect_color: rootWindow.primary_button_color
		anchors{
			horizontalCenter: row_search_params.horizontalCenter
			top: row_search_params.bottom
			margins: rootWindow.pixel_font_size*5
		}
	}

	MyListView {}

}

/*##^##
Designer {
		D{i:0;autoSize:true;formeditorZoom:1.5;height:480;width:640}
}
##^##*/
