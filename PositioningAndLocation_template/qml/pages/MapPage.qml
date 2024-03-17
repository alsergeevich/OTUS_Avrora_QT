import QtQuick 2.6
import Sailfish.Silica 1.0

import QtPositioning 5.3
import QtLocation 5.0
import "../assets"

Page {
    PositionSource { id: positionSource; active: true }
    Map {
        id: map
        anchors.fill: parent
        // ToDo: define plugin to work with OSM
        plugin: Plugin {
            id: plg
            name: "webtiles"
            allowExperimental: true
            PluginParameter {name: "webtiles.scheme"; value: "https"}
            PluginParameter {name: "webtiles.host"; value: "tile.openstreetmap.org"}
            PluginParameter {name: "webtiles.path"; value: "/${z}/${x}/${y}.png"}
            required.mapping: Plugin.AnyMappingFeatures
            required.geocoding: Plugin.AnyGeocodingFeatures
        }

        // ToDo: enable gesture recognition
        gesture.enabled: true

        // ToDo: bind zoomLevel property to slider value
        zoomLevel: zoomSlider.value

        // ToDo: add binding of the map center to the position coordinate
        Binding {
            target: map
            property: "center"
            value: positionSource.position.coordinate
            when: positionSource.position.coordinate.isValid
        }

        Component.onCompleted: {
            center = QtPositioning.coordinate(55.751244, 37.618423);
            map.addMapItem(footprints)
        }

    }
    // ToDo: add a slider to control zoom level
    Slider {
        id: zoomSlider
        color: "grey"
        anchors.bottom: parent.bottom
        width: parent.width
        value: 11
        minimumValue: map.minimumZoomLevel
        maximumValue: map.maximumZoomLevel
    }

    // ToDo: add a component corresponding to MapQuickCircle
    Footprints {
        id: footprints
        coordinate: positionSource.position.coordinate
        visible: positionSource.position.coordinate.isValid
        diameter: Math.min(map.width, map.height) / 8
    }

    // ToDo: add item at the current position
}
