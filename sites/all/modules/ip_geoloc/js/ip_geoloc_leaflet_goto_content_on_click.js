
jQuery(document).bind('leaflet.map', function(event, map, lMap) {

  if (map.settings.gotoContentOnClick) {
    for (var leaflet_id in lMap._layers) {
      lMap._layers[leaflet_id].on('click', function(e) {
        document.location.href = Drupal.settings.basePath + 'node/' + this.feature_id;
      });
    }
  }
  if (map.settings.openBalloonsOnHover) {
    for (var leaflet_id in lMap._layers) {
      lMap._layers[leaflet_id].on('mouseover', function(e) {
        this.openPopup();
      });
    }
  }

});