import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.0

ComboBox {

	property var model_data_array: [ qsTr("Inventory"), qsTr("Sold") ]
	property int cb_width: rootWindow.pixel_font_size_24 * 10
	property int cb_height: rootWindow.pixel_font_size_24 * 1.5

	id:cb
	width: cb_width
	height: cb_height
	font.family: rootWindow.font.family
	font.pixelSize: rootWindow.font.pixelSize
	model: model_data_array

	//the background of the combobox
	background: Rectangle {
		radius: rootWindow.wr*5
		anchors.fill: parent
		color: rootWindow.secondary_color
		border.color: rootWindow.primary_color
		border.width: rootWindow.wr < rootWindow.hr ? rootWindow.wr * 2 : rootWindow.hr * 2
	}

	delegate: ItemDelegate {
		id:itemDlgt
		width: cb.width
		height:rootWindow.pixel_font_size_24 * 1.5
		hoverEnabled: true
		contentItem: Text {
			id:textItem
			text: modelData
			color: rootWindow.primary_text_color
			font: cb.font
			elide: Text.ElideRight
			verticalAlignment: Text.AlignVCenter
			horizontalAlignment: Text.AlignLeft
		}

		background: Rectangle {
			anchors.fill: parent
			color: parent.hovered? rootWindow.secondary_color:rootWindow.primary_color;
			radius: rootWindow.wr*5
			border.color: rootWindow.primary_color
			border.width: parent.hovered? rootWindow.wr*2:0
		}
	}

	//the arrow on the right in the combobox
	indicator: Image {
		width:rootWindow.pixel_font_size_24/2; height:width;
		anchors{
			right: cb.right
			verticalCenter: cb.verticalCenter
			margins: rootWindow.pixel_font_size * 10
		}

		horizontalAlignment:Image.AlignRight
		source: "qrc:/icons/icons/Polygon 1.svg";
	}

	//the text in the combobox
	contentItem: Text {
		text: cb.displayText
		font: cb.font
		color: rootWindow.primary_text_color
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignLeft
		elide: Text.ElideRight
		leftPadding: pixel_font_size_24
	}

	//the list of elements and their style when the combobox is open
	popup: Popup {
		id:comboPopup
		y: cb.height - rootWindow.pixel_font_size
		width: cb.width
		height:contentItem.implicitHeigh
		padding: 0

		contentItem: ListView {
			id:listView
			implicitHeight: contentHeight
			model: cb.popup.visible ? cb.delegateModel : null
			ScrollIndicator.vertical: ScrollIndicator { }
		}

		background: Rectangle {
			anchors.fill: parent
			color: transparent_color
			Rectangle {
				id: cb_bg
				anchors.fill: parent
				border.color: rootWindow.primary_color
				radius: rootWindow.wr*5
				border.width: rootWindow.wr
				color: primary_color
			}
			DropShadow {
				source: cb_bg
				anchors.fill: cb_bg
				radius: 16
				samples: 33
			}
		}
	}

}

