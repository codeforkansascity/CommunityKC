

function custom_js_slugify(text) {
  return text.toString().toLowerCase()
  .replace(/\s+/g, '-')           // Replace spaces with -
  .replace(/[^\w\-]+/g, '')       // Remove all non-word chars
  .replace(/\-\-+/g, '-')         // Replace multiple - with single -
  .replace(/^-+/, '')             // Trim - from start of text
  .replace(/-+$/, '');            // Trim - from end of text
}

function custom_js_initializeMap() {
  L.mapbox.accessToken = "pk.eyJ1IjoiY3RyYWx0ZGVsIiwiYSI6ImNqMjZzNWF5ejAxM2czMnBja3R0MGF4ZHYifQ.b1VwKXqiiKwu7ElTGroVJA";
      var tileSet =  'mapbox.streets';
      var mapboxOSM = L.tileLayer("https://{s}.tiles.mapbox.com/v4/" + tileSet + "/{z}/{x}/{y}.png?access_token="+L.mapbox.accessToken, {
        maxZoom: 19,
        subdomains: ["a", "b", "c", "d"],
        attribution: 'Basemap <a href="https://www.mapbox.com/about/maps/" target="_blank">© Mapbox © OpenStreetMap</a>'
      });
      var mapboxSat = L.tileLayer("https://{s}.tiles.mapbox.com/v4/mapbox.streets-satellite/{z}/{x}/{y}.png?access_token="+L.mapbox.accessToken, {
        maxZoom: 19,
        subdomains: ["a", "b", "c", "d"],
        attribution: 'Basemap <a href="https://www.mapbox.com/about/maps/" target="_blank">© Mapbox © OpenStreetMap</a>'
      });

      var baseLayers = {
        "Street Map": mapboxOSM,
        "Aerial Imagery": mapboxSat
      };
      var map = L.map(document.querySelector('#mapContainer'), {
        zoom: 10,
        layers: [mapboxOSM]
      });
      map.attributionControl.setPrefix("");

      var markerClusters = new L.MarkerClusterGroup({
        spiderfyOnMaxZoom: true,
        showCoverageOnHover: false,
        zoomToBoundsOnClick: true,
        maxClusterRadius: 10
      });

      var featureLayer = L.mapbox.featureLayer();
      featureLayer.once("ready", function(e) {
        map.fitBounds(this.getBounds(), { maxZoom: 17});
      });
      featureLayer.on("ready", function(e) {
        // markerClusters.clearLayers().addLayer(featureLayer);
        // map.addLayer(markerClusters);
        // https://www.mapbox.com/mapbox.js/example/v1.0.0/markercluster-custom-marker-icons/
        var clusterGroup = new L.MarkerClusterGroup({
          iconCreateFunction: function(cluster) {
            var count = cluster.getChildCount();
            var symbol = count > 99 ? 'marker' : count;
            return L.mapbox.marker.icon({
              // show the number of markers in the cluster on the icon.
              'marker-symbol': symbol,
              'marker-color': '#2e3192'
            });
          }
        });
        e.target.eachLayer(function(layer) {
          clusterGroup.addLayer(layer);
        });
        map.addLayer(clusterGroup);
      });
      // https://www.mapbox.com/mapbox.js/example/v1.0.0/markers-with-image-slideshow/
      featureLayer.on('layeradd', (e) => {
        var marker = e.layer;
        var feature = marker.feature;
        var popupContent =  '<div id="' + feature.properties.id + '" class="popup">' +
                          '<h2><a href="/node/"' + feature.properties.nid + '">' + feature.properties.title + '</a></h2>' +
                          '<div class="description">' + feature.properties.description + '</div>';
        if (feature.properties.project_type && feature.properties.project_type.length > 0) {
          popupContent += '<br /><div class="proj-type">Project Type: ';
          for(var t = 0;t<feature.properties.project_type.length;t++) {
            if (t > 0) { popupContent += ', '}
            popupContent += '<a href="/project-type/' + custom_js_slugify(feature.properties.project_type[t]) + '">'
             + feature.properties.project_type[t] + '</a>';
          }
        }
        popupContent += '</div>';
        marker.bindPopup(popupContent, {
          closeButton: true,
          minWidth: 320
        });
      });
      featureLayer.loadURL('/projects/geojson/');
      //return map;
}
