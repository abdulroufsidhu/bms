import QtQuick 2.0
import QtQuick.Controls 2.15


ListView {

	property var lv_model: 6
	property var text_model: "text " + model.index
	property MouseArea first_button_mouse_area
	property MouseArea second_button_mouse_area

	cacheBuffer: rootWindow.pixel_font_size * 40
	id: lv
	width: rootWindow.width
	anchors {
		top: btn_add_item.bottom
		bottom: parent.bottom
	}

	spacing: rootWindow.pixel_font_size*6
	clip: true
	anchors{
		top: btn_add_item.bottom
		bottom:  parent.bottom
		bottomMargin: rootWindow.pixel_font_size*20
	}
	model: lv_model
	delegate: ItemDelegate{
		padding: 0
		width: lv.width
		implicitWidth: lvd_row.implicitWidth
		implicitHeight: lvd_row.implicitHeight
			Row {
				id: lvd_row
				anchors.centerIn: parent
				Text {
					width: rootWindow.pixel_font_size * 400
					height: parent.height
					text: text_model
					font.pixelSize: rootWindow.pixel_font_size_24
					elide: Text.ElideLeft
					verticalAlignment: Text.AlignVCenter
					horizontalAlignment: Text.AlignLeft
					color: rootWindow.primary_text_color
				}
				Image { source: "qrc:/icons/icons/view 1.svg"
				}
				Image { source: "qrc:/icons/icons/sell-label 1.svg"
				}

			}

	}


}
